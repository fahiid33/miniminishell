/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/06/27 19:54:30 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ctl_c()
{
    if (g_vars.pid != 0 && !kill(g_vars.pid, SIGINT))
    {
        ft_putstr_fd("\n", 1);
    }
    else
    {
        ft_putchar_fd('\n', 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
void    ctl_bslash()
{
    if (!kill(g_vars.pid, SIGQUIT))
        ft_putstr_fd("QUIT\n", 1);
   
}
void    c_signal()
{
    signal(SIGQUIT, ctl_bslash);
    signal(SIGINT, ctl_c);
}