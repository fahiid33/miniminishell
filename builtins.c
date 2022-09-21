/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/09/21 22:47:09 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_cmd(t_parse *cmd)
{
	if (builtins_cases(cmd) && !cmd->next->cmd)
		return (1);
	return (0);
}

int	builtins_cases(t_parse *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "cd")
		|| !strcmp(cmd->cmd, "ENV") || !strcmp(cmd->cmd, "PWD")
		|| !strcmp(cmd->cmd, "ECHO") || !ft_strcmp(cmd->cmd, "pwd")
		|| !ft_strcmp(cmd->cmd, "export") || !ft_strcmp(cmd->cmd, "unset")
		|| !ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtins(t_parse *head, t_env **my_env)
{
	head->argv++;
	if (!strcmp(head->cmd, "cd"))
		return (cd(head, (*my_env)));
	else if (!strcmp(head->cmd, "env") || !strcmp(head->cmd, "ENV"))
		return (env());
	else if (!strcmp(head->cmd, "export"))
		return (export(head));
	else if (!strcmp(head->cmd, "pwd") || !strcmp(head->cmd, "PWD"))
		return (pwd());
	else if (strcmp(head->cmd, "exit") == 0)
		return (my_exit(head));
	else if (!strcmp(head->cmd, "echo") || !strcmp(head->cmd, "ECHO"))
		return (echo(head));
	else if (!strcmp(head->cmd, "unset"))
		return (unset(head));
	head->argv--;
	return (0);
}
