/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:33:50 by fahd              #+#    #+#             */
/*   Updated: 2022/06/16 07:06:04 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exit(t_parse *cmd)
{
	check_numb(cmd->argv[0]);
	g_vars.exit_status = atoi(cmd->argv[0]);
	exit (g_vars.exit_status);
}

int	my_exit(t_parse *cmd)
{
	if (!cmd->argv[0])
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		exit(g_vars.exit_status);
	}
	else if (cmd->argv[1])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_vars.exit_status = 1;
		return (g_vars.exit_status);
	}
	run_exit(cmd);
    return (0);
}
