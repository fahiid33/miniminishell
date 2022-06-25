/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:30:26 by fahd              #+#    #+#             */
/*   Updated: 2022/06/25 10:29:55 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_n(t_parse *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!strcmp(cmd->argv[i], "$?"))
			ft_putnbr_fd(g_vars.exit_status, STDOUT_FILENO);
		else
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		i++;
		if (cmd->argv[i])
			write(1, " ", 1);
	}
}
void	echo_e(t_parse *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (!strcmp(cmd->argv[i], "$?"))
			ft_putnbr_fd(g_vars.exit_status, STDOUT_FILENO);
		else
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		i++;
		if (cmd->argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int	echo(t_parse *cmd)
{
	// ft_putnbr_fd(STDOUT_FILENO, 2);
	if (!cmd->argv[0])
	{
		write(STDOUT_FILENO, "\n", 1);
		g_vars.exit_status = 0;
		return (g_vars.exit_status);
	}
	else
	{		
		if (strcmp(cmd->argv[0], "-n") == 0)
			echo_n(cmd);
		else
			echo_e(cmd);
	}
	g_vars.exit_status = 0;
	return (g_vars.exit_status);
}