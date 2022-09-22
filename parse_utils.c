/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by fahd              #+#    #+#             */
/*   Updated: 2022/09/22 04:10:51 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*add_command(t_parse *commad)
{
	t_parse	*new;

	new = init_command();
	commad = lst_add_back_command(commad, new);
	return (commad);
}

t_redir	*init_redir(char *val, int type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = strdup(val);
	redir->next = NULL;
	redir->e_type = type;
	return (redir);
}

t_redir	*lst_add_back_redir(t_redir *lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

t_redir	*add_redir(t_redir *redir, char *val, int type)
{
	t_redir	*new;

	new = init_redir(val, type);
	redir = lst_add_back_redir(redir, new);
	return (redir);
}

char	*jme3arg(t_token **b, int exec)
{
	char	*str;

	str = strdup("");
	while ((*b) && (*b)->flag == 1)
	{
		if ((*b)->e_type == DOLLAR)
		{
			if ((*b)->next->e_type == DQUOTE || (*b)->next->e_type == SQUOTE)
				(*b) = (*b)->next;
			else
			{
				if (!(*b)->val[1])
				{
					(*b) = (*b)->next;
					if (my_getenv(&g_vars.my_env, (*b)->val))
						(*b)->val = my_getenv(&g_vars.my_env, (*b)->val);
					else
						(*b)->val = strdup("");
				}
				else
				{
					if ((*b)->val[1] == ' ' || (*b)->val[1] == '\0')
						str = ft_strjoin(str, strdup("$"), 2);
					else if ((*b)->val[1] == '?')
					{
						str = ft_strjoin(str, strdup("$?"), 2);
					}
					else if ((*b)->val[1] == '$')
					{
						str = ft_strjoin(str, strdup("$$"), 2);
					}
					else
						str = ft_strjoin(str, "69", 2);
					(*b) = (*b)->next;
				}
			}
		}
		if ((*b)->e_type == DQUOTE)
		{
			str = ft_strjoin(str, expand_dollar((*b)->val, 0), 2);
		}
		else if ((*b)->e_type != END)
		{
			str = ft_strjoin(str, (*b)->val, 0);
		}
		if ((*b)->flag == 1)
			(*b) = (*b)->next;
		else
		{
			(*b) = (*b)->next;
			return (str);
		}
	}
	if ((*b) && (*b)->e_type == DOLLAR)
	{
		if (!(*b)->val[1])
		{
			(*b) = (*b)->next;
			if (my_getenv(&g_vars.my_env, (*b)->val))
				(*b)->val = my_getenv(&g_vars.my_env, (*b)->val);
			else
				(*b)->val = strdup("");
		}
		else
		{
			if ((*b)->val[1] == ' ')
			{
				str = ft_strjoin(str, strdup("$"), 2);
			}
			else if (!exec)
				str = ft_strjoin(str, strdup("$?"), 2);
			(*b) = (*b)->next;
			return (str);
		}
	}
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
