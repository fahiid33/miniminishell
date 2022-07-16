
#include "minishell.h"

void pipe_child(t_parse *head, t_env **env,int fd[2])
{
	close(fd[0]);
	dup2(fd[1], 1);
	open_redir(head, 0);
	if (builtins_cases(head))
	{
		g_vars.exit_status = exec_builtins(head, env);
		exit (g_vars.exit_status);
	}
	else
		execute(head, env);
}

void	open_redir(t_parse *head, int exe)
{
	t_redir *tmp;
	int fout;
	int	fin;

	fin = 0;
	fout = 1;
	tmp = head->redir;
	while(tmp != NULL)
	{
		if(tmp->type == GREAT || tmp->type == GREATANDGREAT)
		{
			if(tmp->type == GREAT)
			{
				tmp->fdout = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				fout = tmp->fdout;
			}
			else
			{
				tmp->fdout = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				fout = tmp->fdout;
			}
		}
		else if (tmp->type == LESS || tmp->type == LESSANDLESS)
		{
			if (tmp->type == LESS)
			{	if (access(tmp->file, F_OK) == -1)
				{
					ft_putstr_fd("minishell: no such file or directory: ", 2);
					ft_putstr_fd(tmp->file, 2);
					ft_putchar_fd('\n', 2);
					g_vars.exit_status = 1;
					break ;
				}
				else
				{
					tmp->fdin = open(tmp->file, O_RDONLY);
					fin = tmp->fdin;
				}
			}
			// else
			// {
			// 	tmp->fdin = open("/tmp/heh", O_CREAT | O_RDWR | O_APPEND, 0644);
			// 	fin = tmp->fdin;
			// 	while (strcmp((p = readline(">")) , tmp->file))
			// 	{
			// 		write(tmp->fdin, p, ft_strlen(p));
			// 		write(tmp->fdin, "\n", 1);
			// 	}
			// }	
		}
		tmp = tmp->next;
	}
	if (!exe)
	{
		if (fin != 0)
			dup2(fin, 0);
		if (fout != 1)
			dup2(fout, 1);
	}
}

void pipe_child1(t_parse *head, t_env **env)
{
	open_redir(head, 0);
	execute(head, env);
}

void 	last_execute(t_parse *head, t_env **env)
{
	if (!builtins_cases(head))
	{
    	g_vars.pid = fork();
		if (!g_vars.pid)
		{
			signal(SIGINT, SIG_DFL);
			pipe_child1(head, env);
		}
	}
	else
	{
		open_redir(head, 0);
		g_vars.exit_status = exec_builtins(head, env);
	}
}
void exec_pipeline(t_parse *commands, t_env **env)
{
	t_parse *head;
	int	status;
	int fds[2];
	head = commands;
	fds[0] = dup(0);
	fds[1] = dup(1);
	int fd[2];
	
	if (!head->cmd && head->redir)
		open_redir(head, 1);
	if (head && head->cmd)
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
				{
					signal(SIGINT, SIG_DFL);
					pipe_child(head, env, fd);
				}
				close(fd[1]);
				close(fd[0]);
				head = head->next;
			}
			close(fd[1]);
			close(fd[0]);
        }
		while (waitpid(-1, &status , 0) > 0)
		{
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_vars.exit_status = WTERMSIG(status) + 128;
		}
		if(head->next != NULL)
            last_execute(head, env);
		if (head->cmd)
		{	
			dup2(fds[0], 0);
			dup2(fds[1], 1);
		}
		while (waitpid(-1, &status , 0) > 0)
		{
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_vars.exit_status = WTERMSIG(status) + 128;
		}
	}
}
