/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:17:20 by fahd              #+#    #+#             */
/*   Updated: 2022/05/18 20:59:07 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *sub;
	unsigned int i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

t_lexer	*ft_init_lexer(char *str, char c)
{
    t_lexer			*lexer;

    if (!(lexer = (t_lexer *)malloc(sizeof(t_lexer))))
        return (NULL);
    lexer->str = str; //aka line
    lexer->c = c; // first char of line
    lexer->i = 0; //first index of line
    return (lexer);
}
t_lexer *advance_lexer(t_lexer *lexer)
{
	lexer->i++;
	lexer->c = lexer->str[lexer->i];
	return (lexer);
}
t_token	*send_lexer_to_tokenize(t_lexer *lexer)
{
	t_token			*token;
	char			*val;
	int				type;

	token = NULL;
	while (lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			advance_lexer(lexer);
		else if (lexer->c == '\'')
		{
			type = SQUOTE;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else if (lexer->c == '"')
		{
			type = DQUOTE;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else if (lexer->c == '\\')
		{
			type = BACKSLASH;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else if (lexer->c == '|')
		{
			type = PIPE;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else if (lexer->c == '<')
		{
			if (lexer->i + 1 == '<')
			{
				type = LESSANDLESS;
				val = ft_strsub(lexer->str, lexer->i, 2);
				token = init_token(val, type);
				advance_lexer(lexer);
				free(val);
			}
			else
			{
				type = LESS;
				val = ft_strsub(lexer->str, lexer->i, 1);
				token = init_token(val, type);
				advance_lexer(lexer);
				free(val);
			}
		}
		else if (lexer->c == '>')
		{
			if (lexer->i + 1 == '>')
			{
				type = GREATANDGREAT;
				val = ft_strsub(lexer->str, lexer->i, 2);
				token = init_token(val, type);
				advance_lexer(lexer);
				free(val);
			}
			else
			{
				type = GREAT;
				val = ft_strsub(lexer->str, lexer->i, 1);
				token = init_token(val, type);
				advance_lexer(lexer);
				free(val);
			}
		}
		else if (lexer->c == '|')
		{
			type = PIPE;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else if (lexer->c == '$')
		{
			type = DOLLAR;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
		else
		{
			type = WORD;
			val = ft_strsub(lexer->str, lexer->i, 1);
			token = init_token(val, type);
			advance_lexer(lexer);
			free(val);
		}
	}		
	return (token);		
}