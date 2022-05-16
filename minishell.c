/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/15 20:29:52 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *hak(char *str)
{
	char *str1;
	int flag;
	int i = 0;

	str1 = malloc((int)strlen(str) + 11);
	while (*str)
	{
		flag = 0;
		while(isspace((int)*str))
		{
			str++;
			i++;
		}
		while(*str && isascii((int)*str))
		{
			if(*str == 44 || *str == 34)
				flag++;
			if(*str == '\0' || (isspace((int)*str) && flag == 0) )
				break;
			if (*str == 34 && !isspace(str[i - 1]))
				break;
			str1[i] = *str;
			i++;
			str++;
			if(flag == 2)
				break;
		}
		str1[i] = ',';
		if(flag != 2)
			str1[i + 1] = ' ';
		str++;
		i += 2;
	}
	return &str1[0];
}

int main()
{
    char *line;
    char **args;
    int status;
    char *str;
	str = "";
	while(str && *str != '1')
	{
		str = readline( "minishell :>$ " );
		if(str)
			printf( "%s\n", hak(str));
	}
    // while (1)
    // {
    //     ft_putstr("$> ");
    //     line = ft_read_line("");
    //     args = ft_parse(line); //parsing args
    //     status = ft_execute(args);// exec args , status holds the return value of the executed command
    //     ft_free_2d_array(args); //add history or clear history or exit
    //     free(line);
    // }
    return (0);
}