/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/06/24 09:27:07 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ctl_c()
{
    ft_putchar_fd('\n', 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    c_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ctl_c);
}