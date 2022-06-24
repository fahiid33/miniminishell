/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:32:47 by fahd              #+#    #+#             */
/*   Updated: 2022/06/24 09:23:48 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char *pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	update_export(&g_vars.my_env, "PWD", '=', cwd);	
	update_export(&g_vars.my_env, "OLDPWD", '=', pwd);
}

int home_cd(t_env *env)
{
    char	*home;
	char	*cwd;

    home = my_getenv(&env, "HOME");
	cwd = getcwd(NULL, 0);
    if (!home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        g_vars.exit_status = 1;
        return (g_vars.exit_status);
    }
	if (!chdir(home))
	{
		update_export(&g_vars.my_env, "PWD", '=', my_getenv(&g_vars.my_env, "HOME"));
		update_export(&g_vars.my_env, "OLDPWD", '=', cwd);
		g_vars.exit_status = 0;
	}
	else 
	{
		ft_putstr_fd("minishell: cd: ", 2);
		g_vars.exit_status = 1;	
	}
	return (g_vars.exit_status);
}

int	cd(t_parse *head, t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!head->argv[0] || strcmp(head->argv[0], "~") == 0 || head->argv[0][0] == '\0')
		return (home_cd(env));
	else if (!chdir(head->argv[0]))
	{
		change_pwd(pwd);	
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