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

int main()
{
    char *line;
    char **args;
    int status;

    while (1)
    {
        ft_putstr("$> ");
        line = ft_read_line("");
        args = ft_parse(line); //parsing args
        status = ft_execute(args);// exec args , status holds the return value of the executed command
        ft_free_2d_array(args); //add history or clear history or exit
        free(line);
    }
    return (0);
}