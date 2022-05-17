/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:26:06 by fahd              #+#    #+#             */
/*   Updated: 2022/05/17 22:51:22 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *init_token(char *val, int type)
{
    t_token	*token;
    token = malloc (sizeof (t_token));
    token->val = val;
    token->type = type;
    return (token);
}

t_token *tokenize_WORD(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, WORD));
}
t_token *tokenize_DQUOTE(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '"')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, DQUOTE));
}
t_token *tokenize_SQUOTE(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '\'')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, SQUOTE));
}
t_token *tokenize_GREAT(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '>')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, GREAT));
}
t_token *tokenize_LESS(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '<')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, LESS));
}
t_token *tokenize_PIPE(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '|')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, PIPE));
}
t_token *tokenize_DOllAR(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '$')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, DOLLAR));
}
t_token *tokenize_GREATANDGREAT(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '>')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, GREATANDGREAT));
}
t_token *tokenize_BACKSLASH(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '\\')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, BACKSLASH));
}
t_token *tokenize_LESSANDLESS(char *str, int i)
{
    char *val;
    int j;

    j = 0;
    val = malloc(sizeof(char) * (strlen(str) + 1));
    while (str[i] && str[i] != '<')
    {
        val[j] = str[i];
        j++;
        i++;
    }
    val[j] = '\0';
    printf("%s\n", val);
    return (init_token(val, LESSANDLESS));
}