/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 04:53:30 by fahd              #+#    #+#             */
/*   Updated: 2022/07/30 19:38:31 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrong_cmd()
{
	char	*error;

	error = strerror(errno);
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	if (errno == 2)
	{
		g_vars.exit_status = 127;
		exit(g_vars.exit_status);
	}
	else if (errno == 13 || errno == 21)
	{
		g_vars.exit_status = 126;
		exit(g_vars.exit_status);
	}
	else
	{
		g_vars.exit_status = 1;
		exit(g_vars.exit_status);
	}
}

int	count_env(t_env **env)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*join_3_str(char *s1, char *s2, char *s3)
{
	char *str;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s3)
	{
		while (s3[k])
		{
			str[i + j + k] = s3[k];
			k++;
		}
		str[i + j + k] = '\0';
	}
	else if (s3 == NULL)
		str[i + j] = '\0';
	return (str);
}

char	**env_to_tab(t_env **env)
{
	int		i;
	int		len;
	char	**tab;
	t_env	*tmp;

	i = 0;
	len = count_env(env);
	tmp = (*env);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		tab[i] = join_3_str(tmp->key, "=", tmp->val);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	execute(t_parse *command, t_env **env)
{
	char	*path;
	char 	**new_env;

	new_env = env_to_tab(env);
	path = get_path(command->cmd, new_env);
    if (!command->cmd)
    {
        g_vars.exit_status = 0;
        exit(g_vars.exit_status);
    }
    if (execve(path, command->argv, new_env) == -1)
	    wrong_cmd();
}