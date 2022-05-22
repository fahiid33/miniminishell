/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by fahd              #+#    #+#             */
/*   Updated: 2022/05/22 02:44:33 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse *init_command(void)
{
    t_parse *command;
    
    command = (t_parse *)malloc(sizeof(t_parse));
    command->cmd = NULL;
    command->argv = NULL;
    command->redir = NULL;
    command->next = NULL;
    return (command);
}

t_parse add_command(t_parse *commad)
{
    t_parse *new;

    new = init_command();
    commad = lst_add_back(commad, new);
    return (commad);
}

t_redir *init_redir(char *val, int type)
{
    t_redir *redir;

    if (!(redir = (t_redir *)malloc(sizeof(t_redir))))
        return (NULL);
    redir->val = strdup(val);
    redir->next = NULL;
    redir->type = type;
    return (redir);
}

t_redir *lst_add_back_redir(t_redir *lst, t_redir *new)
{
    t_redir *tmp;

    if (!lst)
        return (new);
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (lst);
}

t_redir *add_redir(t_redir *redir, char *val, int type)
{
    t_redir *new;

    new = init_redir(val, type);
    redir = lst_add_back_redir(redir, new);
    return (redir);
}

void    parse_commands(t_token *token, t_parse *command)
{
    if (token->type == WORD)
    {
        if (!command->cmd)
            command->cmd = strdup(token->val);
        else
            command->argv = lst_add_back(command->argv, init_token(token->val, WORD));
    }
    else if (token->type == GREAT || token->type == LESS
        || token->type == LESSANDLESS || token->type == GREATANDGREAT)
    {
        if (!command->redir)
            command->redir = init_redir(token->val, token->type);
        else
            command->redir = add_redir(command->redir, token->val, token->type);
    }
}
void    create_commands(t_token *token, t_parse *command)
{
    while (token)
    {
        parse_commands(token, command);
        if (token->type == PIPE)
            {
                command = add_command(command);
                command = command->next;
            }
            
        token = token->next;
    }
}