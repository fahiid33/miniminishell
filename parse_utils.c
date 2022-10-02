/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by fahd              #+#    #+#             */
/*   Updated: 2022/10/02 12:45:48 by fstitou          ###   ########.fr       */
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

	redir = (t_redir *)f_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(val);
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
	char	**tmp;

	tmp = (char **) f_malloc(2 * sizeof(char *));
	str = ft_strdup("");
	// if ((*b)->e_type == SQUOTE (*b)->val[1] == '?')
	while ((*b) && (*b)->flag == 1)
	{
		if ((*b)->e_type == DOLLAR)
		{
			if ((*b)->next->e_type == SQUOTE && (*b)->val[1] == '?')
			{
			}
			if (((*b)->next->e_type == DQUOTE || (*b)->next->e_type == SQUOTE)
				&& (*b)->val[1] != '?')
			{
				(*b) = (*b)->next;
			}
			else
			{
				if (!(*b)->val[1])
				{
					(*b) = (*b)->next;
					if ((*b)->val[str_sp_chr((*b)->val)] != '\0'
						&& ((*b)->val)[0] != '0')
					{
						tmp[0] = ft_substr((*b)->val, 0, str_sp_chr((*b)->val));
						tmp[1] = ft_substr((*b)->val, str_sp_chr((*b)->val),
								ft_int_strchr((*b)->val, '\0'));
						if (my_getenv(g_vars.my_env, tmp[0]))
							(*b)->val = ft_strdup(my_getenv(g_vars.my_env,
										tmp[0]));
						else
							(*b)->val = ft_strdup("");
						if (tmp[1][0] == '\\')
							tmp[1]++;
						(*b)->val = ft_strjoin((*b)->val, tmp[1], 0);
					}
					else if (((*b)->val)[0] == '0' && ((*b)->val)[1] != '\0')
					{
						tmp[1] = ((*b)->val) + 1;
						(*b)->val = ft_strdup(my_getenv(g_vars.my_env, "0"));
						(*b)->val = ft_strjoin((*b)->val, tmp[1], 0);
					}
					else
					{
						if (my_getenv(g_vars.my_env, (*b)->val))
							(*b)->val = my_getenv(g_vars.my_env, (*b)->val);
						else
							(*b)->val = ft_strdup("");
					}
				}
				else
				{
					if ((*b)->val[1] == ' ' || (*b)->val[1] == '\0')
						str = ft_strjoin(str, ft_strdup("$"), 2);
					else if ((*b)->val[1] == '?')
					{
						str = ft_strjoin(str, ft_strdup("$?"), 2);
					}
					else if ((*b)->val[1] == '$')
						str = ft_strjoin(str, ft_strdup("$$"), 2);
					else
						str = ft_strjoin(str, "69", 2);
					(*b) = (*b)->next;
				}
			}
		}
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
	// if ((*b)->e_type == SQUOTE && (*b)->val[1] == '?' && (*b)->next->e_type != DQUOTE)
	// {
	// 	g_vars.is_sq = 1;
	// }
	if ((*b) && (*b)->e_type == DOLLAR)
	{
		if (!(*b)->val[1])
		{
			(*b) = (*b)->next;
			if (my_getenv(g_vars.my_env, (*b)->val))
				(*b)->val = my_getenv(g_vars.my_env, (*b)->val);
			else
				(*b)->val = ft_strdup("");
		}
		else
		{
			if ((*b)->val[1] == ' ')
			{
				str = ft_strjoin(str, ft_strdup("$"), 2);
			}
			else if (!exec)
			{
				str = ft_strjoin(str, ft_strdup("$?"), 2);
			}
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
