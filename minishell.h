/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by fahd              #+#    #+#             */
/*   Updated: 2022/05/30 05:57:03 by fstitou          ###   ########.fr       */
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
    int flag;
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

typedef struct s_redir
{
    int     fd;
    char *file;
    int     type;
    struct s_redir *next;

}               t_redir;

typedef struct s_env
{
    char	**env;
	char	**export;

}  		t_env; 

typedef struct s_parse
{
    char *cmd;
    char **argv;
    t_redir *redir;
    struct s_parse *next;
}            t_parse;

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
t_token *lst_add_back(t_token *lst, t_token *new);

char *ft_strsub(t_lexer *lexer, size_t len);
char	*ft_strcharjoin(char *s1, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
int	    ft_isspace(int c);
int	    ft_isalpha(int c);
int	    ft_isdigit(int c);
int	    ft_isalnum(int c);
int	    ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
int	    ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
int	ft_int_strchr(const char *s, int c);
int	token_index(char *str);
char *jme3arg(t_token **b);
int	lst_size(t_token *b);
void    *realloc_array(char **arg, char *str);
t_parse *init_command(void);
void print_l(t_parse *lst);
void create_commands(t_token *token, t_parse **command);
char* expand_dollar(char *dq_content);
void print_list(t_token *lst);
void	builtins(t_parse *commands, t_env *env);
char** init_export(char **env);
int array_size(char **str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin1(char *s1, char *s2 ,int c);
char *pwd(t_parse *head, int k);
void printf_env(char **lenv);
void	add_string_to_env(t_env *env, char *to_add);
int	my_i_getenv(char *str, char **my_env);
void  free_l(char **env);
void	add_string_to_export(t_env *env, char *to_add);
int	my_i_getexp(char *str, char **my_exp);//va
char	*my_getenv(char *str, char **my_env);
void	errors(int exitt);

#endif
