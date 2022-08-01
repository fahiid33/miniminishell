/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:45:13 by fahd              #+#    #+#             */
/*   Updated: 2022/08/01 01:19:01 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_cmd(t_parse *cmd)
{
	if (builtins_cases(cmd) && !cmd->next->cmd)
		return (1);
	return (0);
}

void	dup_pipes(t_parse *cmd, int in, int i, int *fd)
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
}

void	pipe_redir(t_parse *cmd, int in, int index, int *fd)
{
	dup_pipes(cmd, in, index, fd);
	open_redir(cmd, 0);
}

int	append_trunc(t_redir *redir)
{
	int	fout;

	fout = 1;
    if(redir->type == GREAT)
	{
        redir->fdout = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        fout = redir->fdout;
	}
    else
    {
        redir->fdout = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
        fout = redir->fdout;
    }
	return (fout);
}

int	open_read(t_redir *redir, int exec)
{
	int	fin;

	fin = 0;
    if (redir->type == LESS)
    {	
        if (access(redir->file, F_OK) == -1)
        {
            ft_putstr_fd("minishell: no such file or directory: ", 2);
            ft_putstr_fd(redir->file, 2);
            ft_putchar_fd('\n', 2);
            g_vars.exit_status = 1;
			if (exec)
				return (-1);
			exit(g_vars.exit_status);
        }
        else
        {
            redir->fdin = open(redir->file, O_RDONLY);
            fin = redir->fdin;
        }
    }
	else
		dup2(redir->fdin , 0);
	return (fin);
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
			fout = append_trunc(tmp);
		else if (tmp->type == LESS || tmp->type == LESSANDLESS)
		{
			fin = open_read(tmp, exe);
			if (fin == -1)
				break ;
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
