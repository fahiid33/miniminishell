/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:30:26 by fahd              #+#    #+#             */
/*   Updated: 2022/07/04 15:31:38 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_exit(char *exit)
{
	int	i;

	i = 0;
	
	while (exit[i])
	{
		if (exit[i] == '$')
		{
			if (exit[i + 1] == '?')
			{
				ft_putnbr_fd(g_vars.exit_status, STDOUT_FILENO);
				i++;
			}
			else
				write(1, &exit[i], 1);
		}
		else
			write(1, &exit[i], 1);
		i++;
	}
}
void	echo_n(t_parse *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		printf_exit(cmd->argv[i]);
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
		printf_exit(cmd->argv[i]);
		i++;
		if (cmd->argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int	echo(t_parse *cmd)
{
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