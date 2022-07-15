/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/07/15 22:55:41 by fstitou          ###   ########.fr       */
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
        // rl_replace_line("", 0);
        rl_redisplay();
        g_vars.exit_status = 1;
    }
}
void    ctl_bslash()
{
    if (g_vars.pid != 0 && !kill(g_vars.pid, SIGQUIT))
        ft_putstr_fd("QUIT: 3\n", 1);
}
void    c_signal()
{
    signal(SIGQUIT, ctl_bslash);
    signal(SIGINT, ctl_c);
}