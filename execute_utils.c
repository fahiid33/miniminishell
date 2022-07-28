/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 04:53:30 by fahd              #+#    #+#             */
/*   Updated: 2022/07/28 19:42:02 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrong_cmd(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_int_strchr(cmd, 0));
	if (access(cmd, F_OK) == 0 && ((ft_int_strchr(cmd, '.') == 0 && \
		ft_int_strchr(cmd, '/') == 1) || (ft_int_strchr(cmd, '/') == 0)) && \
		access(cmd, X_OK) != 0)
	{
		write(2, ": Permission denied\n", 21);
		g_vars.exit_status = 126;
	}
	else if (access(cmd, F_OK) == 0 && (access(cmd, W_OK) || access(cmd, R_OK)))
	{
		write(2, ": Permission denied\n", 21);
		g_vars.exit_status = 126;
	}
	else if (access(cmd, F_OK) != 0)
	{
		write(2, ": No such file or directory\n", 28);
		g_vars.exit_status = 127;
	}
	else
	{
		write(2, ": command not found\n", 20);
        g_vars.exit_status = 127;
	}
	exit(g_vars.exit_status);
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
	int	i;
	char	**tab;
	t_env	*tmp;
	tmp = (*env);
	int len = count_env(env);
	i = 0;
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
	    wrong_cmd(command->cmd);
}