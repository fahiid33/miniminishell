/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:30:26 by fahd              #+#    #+#             */
/*   Updated: 2022/06/17 13:28:26 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_n(t_parse *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], fd);
		i++;
		if (cmd->argv[i])
			write(fd, " ", 1);
	}
}
void	echo_e(t_parse *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], fd);
		i++;
		if (cmd->argv[i])
			write(fd, " ", 1);
	}
	write(fd, "\n", 1);
}

int	echo(t_parse *cmd, int fd)
{
	if (!cmd->argv[0])
	{
		write(2, "\n", 1);
		g_vars.exit_status = 0;
		return (g_vars.exit_status);
	}
	else
	{		
		if (strcmp(cmd->argv[0], "-n") == 0)
			echo_n(cmd, fd);
		else
			echo_e(cmd, fd);
	}
	g_vars.exit_status = 0;
	return (g_vars.exit_status);
}