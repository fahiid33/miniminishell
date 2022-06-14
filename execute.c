
#include "minishell.h"

int  builtins_cases_sghar(t_parse *head, t_env *env)
{
		head->argv++;
    	if (strcmp(head->cmd, "cd") == 0)
			cd(head, env);
		else if (strcmp(head->cmd, "export") == 0)
			add_export(head, env, 1);
		else if (strcmp(head->cmd, "unset") == 0)
		    unset(head, *env);
        else
		{
			head->argv--;
            return(1);
		}
		head->argv--;
    return(0);	
}
int  builtins_cases(t_parse *head, t_env *env, int fd)
{
		head->argv++;
    	if (strcmp(head->cmd, "cd") == 0)
			cd(head, env);
		else if (strcmp(head->cmd, "env") == 0)
			printf_env(env->env);
		else if (strcmp(head->cmd, "export") == 0)
			add_export(head, env, 0);
		else if (strcmp(head->cmd, "pwd") == 0)
		{
			pwd(head, 0);
						// exit (0);
		}
		else if (strcmp(head->cmd, "exit") == 0)
			my_exit(head);
		else if (strcmp(head->cmd, "echo") == 0)
			echo(head, fd);
		else if (strcmp(head->cmd, "unset") == 0)
		    unset(head, *env);
        else
		{
			head->argv--;
            return(1);
		}
		head->argv--;
    return(0);
}

void pipe_child(t_parse *head, t_env *env,int fd[2])
{
	close(fd[0]);
	dup2(fd[1], 1);
	while(head->redir != NULL)
	{
		close(fd[1]);
		if(head->redir->type == GREAT || head->redir->type == GREATANDGREAT)
		{
			if(head->redir->type == GREAT)
			{
				fd[1] = open(head->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dup2(fd[1], 1);
			}
			else
			{
				fd[1] = open(head->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				dup2(fd[1], 1);
			}
		}
		else
		{
			close(fd[0]);
			fd[0] = open(head->redir->file, O_RDONLY);
			dup2(fd[0], 0);
		}
		head->redir = head->redir->next;
	}
	if(builtins_cases(head,env, fd[1]))
    	execute(head, env->env);
	exit(1);
}
void pipe_child1(t_parse *head, t_env *env,int fd[2])
{
	close(fd[0]);
	while(head->redir != NULL)
	{
		close(fd[1]);
		if(head->redir->type == GREAT || head->redir->type == GREATANDGREAT)
		{
			if(head->redir->type == GREAT)
			{
				fd[1] = open(head->redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dup2(fd[1], 1);
			}
			else
			{
				fd[1] = open(head->redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				dup2(fd[1], 1);
			}
		}
		else
		{
			close(fd[0]);
			fd[0] = open(head->redir->file, O_RDONLY);
			dup2(fd[0], 0);
		}
		head->redir = head->redir->next;
	}
	if(builtins_cases(head,env, 1))
		execute(head, env->env);
	exit(0);
}
void last_execute(t_parse *head, t_env *env, int pid, int fd[2])
{

    	pid = fork();	
		if(pid)
		{
			close(fd[1]);
			builtins_cases_sghar(head, env);
		}
		else
			pipe_child1(head, env,fd);	
		close(fd[1]);
		close(fd[0]);
}

void builtins(t_parse *commands, t_env *env)
{
	t_parse *head;
	int fds[2];
	fds[0] = dup(0);
	head = commands;
	int pid;
	int fd[2];

	if (head)
	{
		if(head->next->next != NULL)
        {
            while(head->next->cmd != NULL)
			{
				pipe(fd);
				pid = fork();
				if(pid)
      			{
      			   close(fd[1]);
      			   dup2(fd[0], 0);
					builtins_cases_sghar(head, env);
      			}
      			else
					 pipe_child(head, env,fd);
				close(fd[1]);
				close(fd[0]);
				head = head->next;
			}
			close(fd[1]);
			close(fd[0]);
        }
		if(head->next != NULL)
            last_execute(head, env, pid, fd);
        dup2(fds[0], 0);
		while (wait(NULL)!= -1);
	}
}
void	wrong_cmd(char *cmd)
{
	if (cmd)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_int_strchr(cmd, 0));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}
void	execute(t_parse *command, char **env)
{
	char	*path;
	if (command->cmd == NULL)
	{
		perror("aaaa");
		exit(127);
	}
	path = get_path(command->cmd, env);
	// perror("SGERrrERGER");
	execve(path, command->argv, env);
	wrong_cmd(command->cmd);
}