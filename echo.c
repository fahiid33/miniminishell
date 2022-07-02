/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:30:26 by fahd              #+#    #+#             */
/*   Updated: 2022/07/02 22:58:46 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_n(t_parse *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!strncmp(cmd->argv[i], "$?", 2))
		{
			ft_putnbr_fd(g_vars.exit_status, STDOUT_FILENO);
			// if ((cmd->argv[i]) + 1)
			// ft_putstr_fd((cmd->argv[i]), STDOUT_FILENO);
		}
		else
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		i++;
		if (cmd->argv[i])
			write(1, " ", 1);
	}
}

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
void	echo_e(t_parse *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (!strncmp(cmd->argv[i], "$?", 2))
			printf_exit(cmd->argv[i]);
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