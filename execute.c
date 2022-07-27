/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 05:11:48 by fahd              #+#    #+#             */
/*   Updated: 2022/07/19 05:11:48 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void pipe_child(t_parse *head, t_env **env)
{
	open_redir(head, 0);
	if (builtins_cases(head))
	{
		g_vars.exit_status = exec_builtins(head, env);
		exit (g_vars.exit_status);
	}
	else
	{
		execute(head, env);
	}
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
int	simple_cmd(t_parse *cmd)
{
	if (builtins_cases(cmd) && !cmd->next->cmd)
		return (1);
	return (0);
}

int	dup_pipes(t_parse *cmd, int in, int i, int *fd)
{
	if (cmd->next->cmd != NULL)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (i != 0)
	{
		dup2(in, 0);
		close(fd[1]);
		close(fd[0]);
	}
	return (0);
}

void	redirect_in_out(t_parse *cmd, int in, int index, int *fd)
{
	int	err;
	err = 0;

	err = dup_pipes(cmd, in, index, fd);
	if (err < 0)
		exit (1);
}

void	exec_pipeline(t_parse *commands, t_env **env)
{
	t_parse *head;
	int	status;
	int fds[2];
	int fd[2];
	int		i;
	int		in;

	head = commands;
	i = 0;
	in = 0;
	if (!head->cmd && head->redir)
	{
		open_redir(head, 1);
		return ;
	}
	if (simple_cmd(head))
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		open_redir(head, 0);
		g_vars.exit_status = exec_builtins(head, env);
		dup2(fds[0], 0);
		dup2(fds[1], 1);
		return ;
	}
	i = 0;
	in = 0;
	while (head->cmd != NULL)
	{
		pipe(fd);
		g_vars.pid = fork();
		if (g_vars.pid == 0)
		{
			redirect_in_out(head, i, in, fd);
			pipe_child(head, env);
		}
		close(fd[1]);
		if (i > 0)
			close(in);
		in = fd[0];
		head = head->next;
		i++;
	}
	while (waitpid(-1, &status , 0) > 0)
	{
		if (WIFEXITED(status))
			g_vars.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_vars.exit_status = WTERMSIG(status) + 128;
	}
}
