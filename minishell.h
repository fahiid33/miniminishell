/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 18:02:35 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
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
    char *str;
    char    c;
    int     i;
}               t_lexer;


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
    } type;
}               t_token;

t_lexer	*ft_init_lexer(char *str, char c);
t_lexer	*send_lexer_to_tokenize(t_lexer *lexer);
#endif