/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/06/23 23:52:13 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ctl_c()
{
    ft_putchar_fd('\n', 1);
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

void    c_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ctl_c);
}