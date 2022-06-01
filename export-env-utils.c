/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-env-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:31:07 by aainhaja          #+#    #+#             */
/*   Updated: 2022/06/01 22:57:24 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**get_string(char **env)
{
	char	**str;
	int		i;
	char	*tmp;

	i = 0;
	while (env[i++])
	str = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup((tmp = ft_substr(env[i] , 0, '=')));
		free(tmp);
		i++;
	}
	str[i++] = NULL;
	return (str);
}
