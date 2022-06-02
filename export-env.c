/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:29:30 by aainhaja          #+#    #+#             */
/*   Updated: 2022/06/02 04:01:42 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_env *env, char *to_add, int size)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	str = (char **)malloc(sizeof (char *) * (size + 1));
	while (env->env[i])
	{
		str[j] = strdup(env->env[i]);
		i++;
		j++;
	}
	str[j] = strdup(to_add);
	str[++j] = NULL;
	env->env = str;
}

void	add_string_to_env(t_env *env, char *to_add)
{
	char	*tmp;
	int		i;
	int		j;
	int		index;
	int		size;

	size = array_size(env->env);
	tmp = ft_substr(to_add, 0, ft_int_strchr(to_add, '=') + 1);
	index = my_i_getenv(tmp, env->env);
	if (index)
	{
		tmp = env->env[index];
		env->env[index] = to_add;
		free(tmp);
	}
	else
		add_to_env(env, to_add, size);
}

void	update_export(t_env *env, char *to_add, int index)
{
	char	*tmp;

	if (ft_int_strchr(env->export[index], '=') != -1)
		tmp = ft_substr(env->export[index], 0,
				ft_int_strchr(env->export[index], '=') + 1);
	else
	{
		tmp = ft_substr(env->export[index], 0,
				ft_int_strchr(env->export[index], '\0'));
		tmp = ft_strjoin(tmp, "=", 0);
	}
	if (ft_int_strchr(to_add, '=') != -1)
	{
		tmp = ft_strjoin(tmp, "\"", 0);
		tmp = ft_strjoin(tmp, ft_substr(to_add,
					ft_int_strchr(to_add, '=') + 1, strlen(to_add)), 2);
		to_add = ft_strjoin(tmp, "\"", 0);
		env->export[index] = to_add;
	}
}

void	add_to_export(t_env *env, char *to_add, int size, char *tmp)
{
	int		j;
	int		i;
	char	**str;

	i = 0;
	j = 0;
	str = (char **)malloc(sizeof (char *) * (size + 1));
	while (env->export[i])
	{
		str[j] = strdup(env->export[i]);
		i++;
		j++;
	}
	to_add = ft_strjoin("declare -x ", to_add, 1);
	if (ft_int_strchr(to_add, '=') != -1)
	{
		tmp = ft_substr(to_add, 0, ft_int_strchr(to_add, '=') + 1);
		tmp = ft_strjoin(tmp, "\"", 0);
		tmp = ft_strjoin(tmp, ft_substr(to_add,
					ft_int_strchr(to_add, '=') + 1, strlen(to_add)), 2);
		to_add = ft_strjoin(tmp, "\"", 0);
	}
		str[j] = strdup(to_add);
		str[++j] = NULL;
		env->export = str;
}

void	add_string_to_export(t_env *env, char *to_add)
{
	char	**str;
	char	*tmp;
	int		y;
	int		index;
	int		size;

	size = array_size(env->export);
	y = ft_int_strchr(to_add, '=');
	if (y == -1)
		y = ft_int_strchr(to_add, '\0');
	tmp = ft_substr(to_add, 0, y);
	index = my_i_getexp(tmp, env->export);
	if (index)
		update_export(env, to_add, index);
	else
		add_to_export(env, to_add, size, tmp);
}

char	**init_export(char	**env)
{
	char	*s1;
	int		i;
	int		j;
	char	**res;

	j = 0;
	s1 = ft_strdup("");
	i = 0;
	while (env[i])
	{
		s1 = ft_strjoin(s1, "declare -x ", 0);
		s1 = ft_strjoin(s1, ft_substr(env[i], 0,
					ft_int_strchr(env[i], '=') + 1), 2);
		s1 = ft_strjoin(s1, "\"", 0);
		s1 = ft_strjoin(s1, strchr(env[j], '=') + 1, 0);
		s1 = ft_strjoin(s1, "\"\n", 0);
		if (strncmp(env[i], "PWD", 3) == 0)
		{
			i++;
			s1 = ft_strjoin(s1, "declare -x OLDPWD\n", 0);
		}
		j++;
		i++;
	}
	res = ft_split(s1, '\n');
	return (res);
}