/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:33:00 by fahd              #+#    #+#             */
/*   Updated: 2022/06/16 07:44:22 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env(void)
{
    t_env *tmp;

    tmp = g_vars.my_env;
    while (tmp)
    {
        if (tmp->sep)
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putchar_fd(tmp->sep, 1);
            if (tmp->val == NULL)
                ft_putchar_fd('\n', 1);
            else
            {
                ft_putstr_fd(tmp->val, 1);
                ft_putchar_fd('\n', 1);
            }
        }
        tmp = tmp->next;
    }
    g_vars.exit_status = 0;
    return (g_vars.exit_status);
}