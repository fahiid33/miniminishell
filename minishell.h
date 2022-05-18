/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by fahd              #+#    #+#             */
/*   Updated: 2022/05/18 02:22:34 by fahd             ###   ########.fr       */
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
# include "42-GNL/get_next_line.h"

# define BUFFER_SIZE 4096 

typedef struct s_lexer
{
    char *str; //aka line
    char    c; // every char in line
    int     i; // index of line
}			t_lexer;

typedef struct s_token
{
    char *val;
    struct s_token *next;
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
t_token *tokenize_WORD(t_lexer *lexer);
t_token *tokenize_DQUOTE(t_lexer *lexer);
t_token *tokenize_SQUOTE(t_lexer *lexer);
t_token *tokenize_GREAT(t_lexer *lexer);
t_token *tokenize_LESS(t_lexer *lexer);
t_token *tokenize_PIPE(t_lexer *lexer);
t_token *tokenize_DOllAR(t_lexer *lexer);
t_token *tokenize_GREATANDGREAT(t_lexer *lexer);
t_token *tokenize_BACKSLASH(t_lexer *lexer);
t_token *tokenize_LESSANDLESS(t_lexer *lexer);
t_token *init_token(char *val, int type);
t_lexer	*advance_lexer(t_lexer *lexer);

#endif