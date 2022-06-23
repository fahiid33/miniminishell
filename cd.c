/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:32:47 by fahd              #+#    #+#             */
/*   Updated: 2022/06/18 22:52:15 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int home_cd(t_env *env)
{
    //repreduce the args array to only have the path
    char *home;

    home = my_getenv(&env, "HOME");
    if (!home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        g_vars.exit_status = 1;
        return (g_vars.exit_status);
    }
	if (!chdir(home))
		g_vars.exit_status = 0;
	else 
	{
		ft_putstr_fd("minishell: cd: ", 2);
		g_vars.exit_status = 1;	
	}
	return (g_vars.exit_status);
}

int	cd(t_parse *head, t_env *env)
{
	if (!head->argv[0] || strcmp(head->argv[0], "~") == 0 || head->argv[0][0] == '\0')
		return (home_cd(env));
	else if (!chdir(head->argv[0]))
	{
		
		g_vars.exit_status = 0;
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(head->argv[0], 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putchar_fd('\n', 2);
		g_vars.exit_status = 1;
	}
	return (g_vars.exit_status);
}