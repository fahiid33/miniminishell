/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-env-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:31:07 by aainhaja          #+#    #+#             */
/*   Updated: 2022/06/13 02:06:11 by fstitou          ###   ########.fr       */
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

int	ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (*to_find == '\0')
		return (0);
	i = 0;
	while (str[i] && (size_t) i < len)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (str[i] && str[i + j] == to_find[j] && (size_t)(i + j) < len)
			{
				j++;
				if (to_find[j] == '\0')
					return (i);
			}
		}
		i++;
	}
	return (0);
}

void	perr_exp(char *str)  //k+=
{
	int	i;

	i = 0;
	if (ft_strnstr(str, "+=", strlen(str)))
	{
		while (str[i] && str[i] != '+')
		{
			if (!ft_isalnum(str[i]))
			{
				printf("bash: export: %s : not a valid identifier \n", str);
				exit(1);
			}
			i++;
		}
	}
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]))
			{
				printf("bash: export: %s : not a valid identifier \n", str);
				exit(1);
			}
			i++;
		}
	}
	
}
int	check_env_string(char *str)//k+=
{
	int	i;

	i = 0;

	perr_exp(str);
	while (str[i])
	{
		// perror("AAAAAAAAAA");
		if (str[i] == '+' && str[i + 1] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}