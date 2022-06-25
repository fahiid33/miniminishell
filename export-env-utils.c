/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-env-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:31:07 by aainhaja          #+#    #+#             */
/*   Updated: 2022/06/25 10:09:58 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

//split the string with char c
t_env	*lst_new(char *key, char sep, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->val = val;
	new->sep = sep;
	new->next = NULL;
	return (new);
}
//add new to lst
void	lst_add_backenv(t_env **lst, t_env *new)
{
	t_env	*tmp;
	tmp = *lst;

	if (!new)
		return ;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*init_env(char **env)
{
	char	*key;
	char	*val;
	int	i;
	t_env	*new;
	char **tmp;
	new = g_vars.my_env;
	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');	
		key = tmp[0];
		val = tmp[1];
		lst_add_backenv(&new, lst_new(key, '=', val));
		i++;
	}
	return (new);
}

char	*my_getenv(t_env  **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}
void	check_numb(char *str)
{
	int	i;

	i = 0;	
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("bash: exit: numeric argument required\n", 2);
			g_vars.exit_status = 255;
			exit (g_vars.exit_status);
		}
		i++;
	}
}
