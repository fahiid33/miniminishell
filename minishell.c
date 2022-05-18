/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/18 01:31:20 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char *av[], char **env)
{
   char	*line;
   int	i = 0;
   line = readline("Minishell ");
   t_lexer	*test;
   t_token *test1;
   test = malloc(sizeof(t_lexer));
   test = ft_init_lexer(line, line[0]);//initilize the lexer
   test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
	// print_list(test1);
}