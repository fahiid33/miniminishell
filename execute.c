
#include "minishell.h"

void pipe_child(t_parse *head, t_env **env,int fd[2])
{
	close(fd[0]);
	dup2(fd[1], 1);
	open_redir(head, fd);
	if(builtins_cases(head))
	{
		g_vars.exit_status = exec_builtins(head, env);
		exit(g_vars.exit_status);
	}
	else
		execute(head, env);
}

void	open_redir(t_parse *head, int fd[2])
{
	(void)fd;
	while(head->redir != NULL)
	{
		if(head->redir->type == GREAT || head->redir->type == GREATANDGREAT)
		{
			if(head->redir->type == GREAT)
			{
				// close(fd[1]);
				head->redir->fd = open(head->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dup2(head->redir->fd, STDOUT_FILENO);
				// ft_putnbr_fd(head->redir->fd, 2);
				// ft_putstr_fd("\n\n", 2);
			}
			else
			{
				// close(fd[1]);
				head->redir->fd = open(head->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				dup2(head->redir->fd, STDOUT_FILENO);
				
			}
		}
		else
		{
			// close(fd[0]);
			head->redir->fd = open(head->redir->file, O_RDONLY);
			dup2(head->redir->fd, 0);
		}
		head->redir = head->redir->next;
	}
}

void pipe_child1(t_parse *head, t_env **env, int fd[2])
{
	open_redir(head, fd);
	if(builtins_cases(head))
	{
		g_vars.exit_status = exec_builtins(head, env);
		exit(g_vars.exit_status);
	}
	else
		execute(head, env);
}

void 	last_execute(t_parse *head, t_env **env, int fd[2])
{
	int	status;
	if (!builtins_cases(head))
	{
    	g_vars.pid = fork();	
		if(g_vars.pid)
		{
			waitpid(g_vars.pid, &status, 0);
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
		}
		else
			pipe_child1(head, env,fd);	

	}
	else
	{
		open_redir(head, fd);
		g_vars.exit_status = exec_builtins(head, env);
	}
}

void exec_pipeline(t_parse *commands, t_env **env)
{

	t_parse *head;
	int	status;
	int fds;
	head = commands;
	fds = dup(0);
	int fd[2];
	if (head)
	{
		if(head->next->next != NULL)
        {
            while(head->next->cmd != NULL)
			{
				pipe(fd);
				g_vars.pid = fork();
				if(g_vars.pid)
      			{
      			   close(fd[1]);
      			   dup2(fd[0], 0);
      			}
      			else
					 pipe_child(head, env, fd);
				close(fd[1]);
				close(fd[0]);
				head = head->next;
			}
			close(fd[1]);
			close(fd[0]);
        }
		if(head->next != NULL)
            last_execute(head, env, fd);
		dup2(fds, 0);
		while (waitpid(-1, &status , 0) > 0)
		{
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
		}
	}
}
