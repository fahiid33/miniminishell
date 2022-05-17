/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 17:56:46 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
   char	*line;
   int	i = 0;
   t_lexer	*test;
   test = malloc(sizeof(t_lexer));
   test = ft_init_lexer(line, line[0]);//initilize the lexer
   test = send_lexer_to_tokenize(test);//tokenizing every char in the line
}