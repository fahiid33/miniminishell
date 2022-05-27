
#include "minishell.h"

t_token	*send_lexer_to_tokenize(t_lexer *lexer)
{
	t_token			*token;
	t_token			*tmp;
	char			*val;
	int				type;
	int size = 0;
	
	tmp = NULL;
	token = NULL;
	while (lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			advance_lexer(lexer);
		else if (lexer->c == '\'')
		{
			advance_lexer(lexer);
			type = SQUOTE;
			if	(ft_int_strchr(&(lexer->str[lexer->i]), '\'') >= 0)
				size = ft_int_strchr(&(lexer->str[lexer->i]), '\'');
			else
				size = ft_int_strchr(&(lexer->str[lexer->i]), '\0');
			val = ft_strsub(lexer, size);
			advance_lexer(lexer);
			token = init_token(val, type);
			if(lexer->c != ' ' && lexer->c != '\0')
				token->flag = 1;
			tmp = lst_add_back(tmp, token);
		}
		else if (lexer->c == 34)
		{
			type = DQUOTE;
			advance_lexer(lexer);
			if	(ft_int_strchr(&(lexer->str[lexer->i]), 34) >= 0)
				size = ft_int_strchr(&(lexer->str[lexer->i]), 34);
			else
				size = ft_int_strchr(&(lexer->str[lexer->i]), '\0');
			val = ft_strsub(lexer, size);
			advance_lexer(lexer);
			token = init_token(val, type);
			if(lexer->c != ' ' && lexer->c != '\0')
				token->flag = 1;
			tmp = lst_add_back(tmp, token);
		}
		else if (lexer->c == '|')
		{
			type = PIPE;
			val = ft_strsub(lexer, 1);
			token = init_token(val, type);
			tmp = lst_add_back(tmp, token);
		}
		else if (lexer->c == '<')
		{
			if (lexer->str[lexer->i + 1] == '<')
			{
				type = LESSANDLESS;
				val = ft_strsub(lexer, 2);
				token = init_token(val, type);
				tmp = lst_add_back(tmp, token);
				}
			else
			{
				type = LESS;
				val = ft_strsub(lexer, 1);
				token = init_token(val, type);
				tmp = lst_add_back(tmp, token);
				}
		}
		else if (lexer->c == '>')
		{
			if (lexer->str[lexer->i+1] == '>')
			{
				type = GREATANDGREAT;
				val = ft_strsub(lexer, 2);
				token = init_token(val, type);
				tmp = lst_add_back(tmp, token);
				}
			else
			{
				type = GREAT;
				val = ft_strsub(lexer, 1);
				token = init_token(val, type);
				tmp = lst_add_back(tmp, token);
				}
		}
		else if (lexer->c == '$')
		{
			type = DOLLAR;
			val = ft_strsub(lexer, 1);
			token = init_token(val, type);
			if(lexer->c != ' ' && lexer->c != '\0')
				token->flag = 1;
			tmp = lst_add_back(tmp, token);
		}
		else
		{
			type = WORD;
			if(token_index(&(lexer->str[lexer->i])))
				size = token_index(&(lexer->str[lexer->i]));
			else if	(ft_int_strchr(&(lexer->str[lexer->i]), ' ') > 0)
				size = ft_int_strchr(&(lexer->str[lexer->i]), ' ');
			else
				size = ft_int_strchr(&(lexer->str[lexer->i]), '\0');
			val = ft_strsub(lexer, size);
			token = init_token(val, type);
			if(lexer->c != ' ' && lexer->c != '\0')
				token->flag = 1;
			tmp = lst_add_back(tmp, token);
		}
	}
	token = init_token("", END);
	tmp = lst_add_back(tmp, token);
	return (tmp);		
}