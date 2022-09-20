/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/07/31 02:25:45 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT && !g_vars.exit_sig)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_vars.exit_status = 1;
	}
	else if (sig == SIGINT && g_vars.exit_sig == 1)
	{
		g_vars.exit_status = 1;
		exit(g_vars.exit_status);
	}
	else if (sig == SIGQUIT)
	{
		ft_putchar_fd('\r', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(int sig)
{
	if (!kill(g_vars.pid, sig))
	{
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_vars.exit_status = 131;
		}
		else if (sig == SIGINT )
		{
			ft_putstr_fd("hiya\n", 1);
			g_vars.exit_status = 130;
		}
	}
	else
		sig_child(sig);
}

void	ctl_plus(int sig)
{
	if (g_vars.pid != 0)
		sig_handler(sig);
	else
		sig_child(sig);
}

void	c_signal(void)
{
	signal(SIGINT, ctl_plus);
	signal(SIGQUIT, ctl_plus);
}