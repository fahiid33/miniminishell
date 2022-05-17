/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 22:49:32 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **env)
{
   char	*line;
   int	i = 0;
   line = readline(">$");
   t_lexer	*test;
   t_token *test1;
   test = malloc(sizeof(t_lexer));
   test = ft_init_lexer(line, line[0]);//initilize the lexer
   test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
	// print_list(test1);
}