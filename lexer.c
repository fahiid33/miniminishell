/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:17:20 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 17:59:54 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_lexer	*send_lexer_to_tokenize(t_lexer *lexer)
{
	t_lexer->i = 0;
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == ' ' || lexer->str[lexer->i] == '\t')
			lexer->i++;
		else if (lexer->str[lexer->i] == '\'')
			lexer = tokenize_SQUOTE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '"')
			lexer = tokenize_DQUOTE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '>')
		{
			if (lexer->str[lexer->i + 1] == '>')
				lexer = tokenize_GREATANDGREAT(lexer->str, lexer->i);
			else
				lexer = tokenize_GREAT(lexer->str, lexer->i);
		}
		else if (lexer->str[lexer->i] == '<')
		{
			if (lexer->str[lexer->i + 1] == '<')
				lexer = tokenize_LESSANDLESS(lexer->str, lexer->i);
			else
				lexer = tokenize_LESS(lexer->str, lexer->i);
		}
		else if (lexer->str[lexer->i] == '|')
			lexer = tokenize_PIPE(lexer->str, lexer->i);
		else if (lexer->str[lexer->i] == '\\')
			lexer = tokenize_BACKSLASH(lexer->str, lexer->i);
		else
			lexer = tokenize_WORD(lexer->str, lexer->i);
	}
}