
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
void closeredir(t_redir *head)
{
	t_redir *tmp;
	tmp = head;
	while(tmp)
	{
		if(tmp->type == GREAT || tmp->type == GREATANDGREAT)
		{
			close(tmp->fdout);
		}
		tmp = tmp->next;
	}
}
void	open_redir(t_parse *head, int fd[2])
{
	(void)fd;
	t_redir *tmp;
	int fout;

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
				// close(fd[1]);
				tmp->fdout = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				fout = tmp->fdout;
			}
		}
		else
		{
			if (access(tmp->file, F_OK) == -1)
			{
				ft_putstr_fd("minishell: no such file or directory: ", 2);
				ft_putstr_fd(tmp->file, 2);
				ft_putchar_fd('\n', 2);
				g_vars.exit_status = 1;
				return ;
			}
			else
			{
				tmp->fdin = open(tmp->file, O_RDONLY);
				dup2(tmp->fdin, 0);
				close(tmp->fdin);
			}
		}
		tmp = tmp->next;
	}
	dup2(fout, 1);
	close(fout);
	ft_putnbr_fd(fout,2);
	ft_putchar_fd('\n',2);
}

void pipe_child1(t_parse *head, t_env **env, int fd[2])
{
	open_redir(head, fd);
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
		{
			signal(SIGINT, SIG_DFL);
			pipe_child1(head, env,fd);	
		}
	}
	else
	{
		open_redir(head, fd);
		if((g_vars.pid = fork()) == 0)
		{
			signal(SIGINT, SIG_DFL);
			g_vars.exit_status = exec_builtins(head, env);
			close(STDOUT_FILENO);
			exit(g_vars.exit_status);
		}
		else
		{
			waitpid(g_vars.pid, &status, 0);
			close(STDOUT_FILENO);
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
		}
	}
}

void exec_pipeline(t_parse *commands, t_env **env)
{
	// ft_putstr_fd(commands->cmd, 2);
	t_parse *head;
	int	status;
	int fds;
	head = commands;
	fds = dup(0);
	int fd[2];
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
		if(head->next != NULL)
            last_execute(head, env, fd);
		dup2(fds, 0);
		while (waitpid(-1, &status , 0) > 0)
		{
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
		}
	}
	if (!head->cmd && head->redir)
	{
		// ft_putstr_fd("WAAAAAAAAAAAAA\n\n", 2);
		while (head->redir)
		{
			head->redir->fdin = 0;
			head->redir->fdout = 1;
			if(head->redir->type == GREAT || head->redir->type == GREATANDGREAT)
			{
				if(head->redir->type == GREAT)
				{
					head->redir->fdout = open(head->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
					dup2(head->redir->fdout, STDOUT_FILENO);
					close(head->redir->fdout);
				}
				else
				{
					head->redir->fdout = open(head->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
					dup2(head->redir->fdout, STDOUT_FILENO);
					close(head->redir->fdout);
				}
			}
			else
			{
				if (access(head->redir->file, F_OK) == -1)
				{
					ft_putstr_fd("minishell: no such file or directory: ", 2);
					ft_putstr_fd(head->redir->file, 2);
					ft_putchar_fd('\n', 2);
					g_vars.exit_status = 1;
					return ;
				}
				else
				{
					head->redir->fdin = open(head->redir->file, O_RDONLY);
					dup2(head->redir->fdin, 0);
					close(head->redir->fdin);
				}
			}
			head->redir = head->redir->next;
		}
		return;
	}
}
