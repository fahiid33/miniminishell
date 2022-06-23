/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:33:17 by fahd              #+#    #+#             */
/*   Updated: 2022/06/16 08:11:39 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(void)
{
	char    *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        ft_putstr_fd("pwd: cannot get current working directory\n", 2);
        g_vars.exit_status = 1;
        return (g_vars.exit_status);
    }
	printf("%s\n", cwd);
    // ft_putstr_fd(cwd, 1);
    // ft_putstr_fd("\n", 1);
    // free(cwd);
    g_vars.exit_status = 0;
    return (g_vars.exit_status);
}
