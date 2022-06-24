
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
	while(head->redir != NULL)
	{
		if(head->redir->type == GREAT || head->redir->type == GREATANDGREAT)
		{
			if(head->redir->type == GREAT)
			{
				// close(fd[1]);
				head->redir->fd = open(head->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dup2(head->redir->fd, 1);
			}
			else
			{
				// close(fd[1]);
				head->redir->fd = open(head->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				dup2(head->redir->fd, 1);
			}
		}
		else
		{
			close(fd[0]);
			head->redir->fd = open(head->redir->file, O_RDONLY);
			dup2(head->redir->fd, 0);
		}
		head->redir = head->redir->next;
	}
}

void pipe_child1(t_parse *head, t_env **env, int fd[2])
{
	// close(fd[0]);
	// dup2(fd[1], 1);
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
	if (!builtins_cases(head))
	{
    	g_vars.pid = fork();	
		if(g_vars.pid)
		{
			waitpid(g_vars.exit_status, NULL, 0);
			// close(fd[1]);
			// // dup2(fd[0], 0);
	
		}
		else
			pipe_child1(head, env,fd);	

	}
	else
	{
		open_redir(head, fd);
		exec_builtins(head, env);
		// close(fd[1]);
		// close(fd[0]);
	}
		// close(fd[1]);
		// close(fd[0]);
}
// void	wait_childs(void)
// {
// 	int status;
// 	while(waitpid(g_vars.pid, &status, WUNTRACED) != -1)
// 	{
// 		if(WIFEXITED(status))
// 			g_vars.exit_status = WEXITSTATUS(status);
// 	}
// }

// void	child(t_parse *cmd, t_env **env)
// {
// 	int		pipefd[2];
// 	g_vars.pid = fork();

// 	pipe(pipefd);
// 	if (!g_vars.pid)
// 	{
// 		// close(pipefd[0]);
// 		// dup2(pipefd[1], 1);
// 		if (cmd->redir)
// 		{
// 			cmd->fdin = 0;
// 			cmd->fdout = 1;
// 			while(cmd->redir)
// 			{
// 				if(cmd->redir->type == GREAT || cmd->redir->type == GREATANDGREAT)
// 				{
// 					if(cmd->redir->type == GREAT)
// 					{
// 						close(pipefd[1]);
// 						cmd->redir->fd = open(cmd->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 						cmd->fdout = cmd->redir->fd;
	
// 					}
// 					else
// 					{
// 						close(pipefd[1]);
// 						cmd->redir->fd = open(cmd->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 						cmd->fdout = cmd->redir->fd;
						
// 					}
// 				}
// 				else if(cmd->redir->type == LESS || cmd->redir->type == LESSANDLESS)
// 				{
// 					if(cmd->redir->type == LESS)
// 					{
// 						close(pipefd[0]);
// 						cmd->redir->fd = open(cmd->redir->file, O_RDONLY);
// 						cmd->fdin = cmd->redir->fd;
// 					}
// 				}
// 				cmd->redir = cmd->redir->next;
// 			}
// 			if (cmd->fdin != 0)
// 				dup2(cmd->fdin, 0);
// 			if (cmd->fdout != 1)
// 				dup2(cmd->fdout, 1);
// 		}
// 		if (builtins_cases(cmd))
// 			exec_builtins(cmd, env, 1);
// 		else
// 			execute(cmd, env);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		wait_childs();
// 	}
// }

void exec_pipeline(t_parse *commands, t_env **env)
// {
// 	t_parse	*cmd;
// 	// int	fds;

// 	cmd = commands;
// 	// fds = STDIN_FILENO;
// 		if (cmd->next->next)
// 		{
// 			while (cmd->next->cmd)
// 			{
				
// 				signal(SIGINT, SIG_DFL);
// 				child(cmd, env);
// 				cmd = cmd->next;
// 			}
// 		}
// }
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
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				g_vars.exit_status = WEXITSTATUS(status);
		}
	}
}
