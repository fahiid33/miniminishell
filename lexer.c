/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:17:20 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 22:50:27 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_init_lexer(char *str, char c)
{
    t_lexer			*lexer;

    if (!(lexer = (t_lexer *)malloc(sizeof(t_lexer))))
        return (NULL);
    lexer->str = str;//aka line
    lexer->c = c;// first char of line
    lexer->i = 0;//first index of line
    return (lexer);
}
t_token	*send_lexer_to_tokenize(t_lexer *lexer)
{
	t_token *token;
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == ' ' || lexer->str[lexer->i] == '\t')
			lexer->i++;
		else if (lexer->str[lexer->i] == '\'')
			token = tokenize_SQUOTE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '"')
			token = tokenize_DQUOTE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '>')
		{
			if (lexer->str[lexer->i + 1] == '>')
				token = tokenize_GREATANDGREAT(lexer->str, lexer->i);
			else
				token = tokenize_GREAT(lexer->str, lexer->i);
		}
		else if (lexer->str[lexer->i] == '<')
		{
			if (lexer->str[lexer->i + 1] == '<')
				token = tokenize_LESSANDLESS(lexer->str, lexer->i);
			else
				token = tokenize_LESS(lexer->str, lexer->i);
		}
		else if (lexer->str[lexer->i] == '|')
			token = tokenize_PIPE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '\\')
			token = tokenize_BACKSLASH(lexer->str, lexer->i);
		else
			token = tokenize_WORD(lexer->str, lexer->i);
	}
}