/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 02:29:19 by fahd              #+#    #+#             */
/*   Updated: 2022/09/15 20:31:38 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*random_filename()
{
	static	int nb_file = 0;
	char	*filename;
	char	*filename_nb;

	nb_file++;
	filename_nb = ft_itoa(nb_file);
	filename = ft_strjoin("/tmp/file", filename_nb, -1);
	free(filename_nb);
	return (filename);
}

int	open_heredoc(char *limiter, char *filename)
{
	int	fd;
	char	*doc;
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		c_signal();
		doc = readline(">");
		if (!doc)
		{
			break ;
		}
		if (!ft_strcmp(doc, limiter))
		{
			if (doc)
				free(doc);
			break;
		}
		ft_putstr_fd(doc, fd);
		ft_putchar_fd('\n', fd);
		if (doc)
			free(doc);
	}
	close(fd);
	fd = open(filename, O_RDONLY, 0644);
	return (fd);
}
	
void	read_heredocs(t_parse *command)
{
	t_redir *redir;
	t_parse *cmd;
	char	*tmpfile;
	
	cmd = command;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == LESSANDLESS && redir->file)
			{
				tmpfile = random_filename();
				redir->fdin = open_heredoc(redir->file, tmpfile);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}