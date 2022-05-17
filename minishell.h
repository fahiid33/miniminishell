/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 22:44:09 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
    char *str; //aka line
    char    c; // every char in line
    int     i; // index of line
}			t_lexer;

typedef struct s_token
{
    char *val;
    enum
    {
        WORD,
        DQUOTE,
        SQUOTE,
        BACKSLASH,
        PIPE,
        GREATANDGREAT,
        LESSANDLESS,
        GREAT,
        LESS,
        DOLLAR,
		END,
    } type;
}               t_token;

t_lexer	*ft_init_lexer(char *str, char c);
t_token	*send_lexer_to_tokenize(t_lexer *lexer);
t_token *tokenize_WORD(char *str, int i);
t_token *tokenize_DQUOTE(char *str, int i);
t_token *tokenize_SQUOTE(char *str, int i);
t_token *tokenize_GREAT(char *str, int i);
t_token *tokenize_LESS(char *str, int i);
t_token *tokenize_PIPE(char *str, int i);
t_token *tokenize_DOllAR(char *str, int i);
t_token *tokenize_GREATANDGREAT(char *str, int i);
t_token *tokenize_BACKSLASH(char *str, int i);
t_token *tokenize_LESSANDLESS(char *str, int i);
t_token *init_token(char *val, int type);
#endif