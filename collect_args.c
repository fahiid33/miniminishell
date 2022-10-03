/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:14 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/03 05:14:07 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*normal_or_qu(t_token **b, int exec)
{
	if (!(*b)->val[1])
		return (normal_expansion(b, 1));
	else
		return (dollar_qu(b, exec));
}

char	*dollar_qu(t_token **b, int exec)
{
	char	*str;

	str = ft_strdup("");
	(*b) = (*b)->next;
	if (!exec)
		str = ft_strjoin(str, ft_strdup("$?"), 2);
	else if ((*b)->val[1] == ' ')
		str = ft_strjoin(str, ft_strdup("$"), 2);
	return (str);
}

char	*check_end(t_token **b, char *str)
{
	if ((*b) && (*b)->e_type == DQUOTE)
	{
		str = ft_strjoin(str, expand_dollar((*b)->val, 0), 2);
		(*b) = (*b)->next;
	}
	else if ((*b) && (*b)->e_type != END)
	{
		str = ft_strjoin(str, (*b)->val, 0);
		(*b) = (*b)->next;
	}
	return (str);
}

char	*jme3arg(t_token **b, int exec)
{
	char	*str;

	str = ft_strdup("");
	while ((*b) && (*b)->flag == 1)
	{
		if ((*b)->e_type == DOLLAR)
			checkin_dollar(b, str);
		if ((*b)->e_type == DQUOTE)
			str = ft_strjoin(str, expand_dollar((*b)->val, 0), 2);
		else if ((*b)->e_type != END)
			str = ft_strjoin(str, (*b)->val, 0);
		if ((*b)->flag == 1)
			(*b) = (*b)->next;
		else
		{
			(*b) = (*b)->next;
			return (str);
		}
	}
	if ((*b) && (*b)->e_type == DOLLAR)
		return (normal_or_qu(b, exec));
	str = check_end(b, str);
	return (str);
}
