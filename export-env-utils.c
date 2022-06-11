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

char	*my_getenv(char *str, char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		if (strncmp(str, my_env[i], strlen(str)))
			return (ft_substr(my_env[i], strlen(str), strlen(my_env[i])));
		i++;
	}
	return (NULL);
}

int	my_i_getenv(char *str, char **my_env) //PWD=
{
	int	i;

	i = 0;
	// printf("to_add==%s\n\n", str);
	while (my_env[i])
	{
		if (strncmp(str, my_env[i], ft_int_strchr(my_env[i], '=')) == 0)
		{
			return (i);	
		}
		i++;
	}
	return (0);
}

int	my_i_getexp(char *str, char **my_exp) //var=
{
	int	i;

	i = 0;
	while (my_exp[i])
	{
		if(ft_int_strchr(ft_strchr(my_exp[i],'x'), '=') - 2 > 0)
		{
			if (strcmp(str, ft_substr(my_exp[i], 11, ft_int_strchr(ft_strchr(my_exp[i],'x'), '=') - 2)) == 0)
				return (i);
		}
		else if (strcmp(str, ft_substr(my_exp[i], 11, ft_int_strchr(ft_strchr(my_exp[i],'x'), '\0') - 2)) == 0)
				return (i);
		i++;
	}
	return (0);
}

void printf_env(char **lenv)
{
	int i;

	i = 0;
	while (lenv[i])
	{
		printf("%s\n", lenv[i]);
		i++;
	}
	// exit (0);
}

int	perr_exp(char *str)
{
	int	i;
	i = 0;
	while(str && str[i]&& str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
		{
			printf("bash: export: %s : not a valid identifier \n", ft_substr(str, 0, ft_int_strchr(str, '=')));
			return (1);
		}
		if (str[i] == '+' && str[i + 1] == '=')
		{
			
		}
		i++;
	}
	return(0);
}