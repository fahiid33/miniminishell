/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by fahd              #+#    #+#             */
/*   Updated: 2022/05/29 06:59:52 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse *init_command(void)
{
    t_parse *command;
    
    command = (t_parse *)malloc(sizeof(t_parse));
    command->cmd = NULL;
    command->argv = (char **)realloc_array(NULL,strdup(""));
    command->redir = NULL;
    command->next = NULL;
    return (command);
}

t_parse *lst_add_back_command(t_parse *lst, t_parse *new)
{
    t_parse *tmp;

    if (!lst)
        return (new);
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (lst);
}

t_parse *add_command(t_parse *commad)
{
    t_parse *new;

    new = init_command();
    commad = lst_add_back_command(commad, new);
    return (commad);
}

t_redir *init_redir(char *val, int type)
{
    t_redir *redir;

    if (!(redir = (t_redir *)malloc(sizeof(t_redir))))
        return (NULL);
    redir->file = strdup(val);
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

void    parse_commands(t_token **token, t_parse *command)
{
    char *value;
    int type;
    if ((*token)->type == WORD ||  (*token)->type == DQUOTE || (*token)->type == SQUOTE || (*token)->type == DOLLAR)
    {
        value = jme3arg(token);
        if (!command->cmd)
           command->cmd = value;
        else
            command->argv = (char **)realloc_array(command->argv,value);
    }
    else if ((*token)->type == GREAT || (*token)->type == LESS
        || (*token)->type == LESSANDLESS || (*token)->type == GREATANDGREAT)
    {
        type = (*token)->type;
        (*token) = (*token)->next;
        value = jme3arg(token);
        if (!command->redir)
            command->redir = init_redir(value, type);
        else
            command->redir = add_redir(command->redir, value, type);
    }
}
void create_commands(t_token *token, t_parse **command)
{
    t_parse *head;

    head = *command;
    while (token)
    {
        parse_commands(&token, head);
        if (token->type == PIPE || token->type == END)
        {
            head = add_command(head);
            //  while(head->redir)
            // {
            //     printf("%d - %s ; ", head->redir->type,head->redir->file);
            //     head->redir = head->redir->next;
            // }
            // head->fd_in = get_fd(head->redir);
            head = head->next;
            token = token->next;
        }
    }
    
}

char *jme3arg(t_token **b)
{
	int	len;
    char *str;

    str = strdup("");
	len = 0;
	while ((*b) && (*b)->flag == 1)
	{
        if((*b)->type == DOLLAR)
        {
            if((*b)->next->type == DQUOTE || (*b)->next->type == SQUOTE)
                (*b) = (*b)->next;
            else{
                if(!(*b)->val[1])
                {
                    (*b) = (*b)->next;
                    if(getenv((*b)->val))
                        (*b)->val = getenv((*b)->val);
                    else
                        (*b)->val = strdup("");
                }
                else
                {
                    if((*b)->val[1] == ' ')
                        str = ft_strjoin(str, strdup("$"));
                    (*b) = (*b)->next;
                }
            }
            
        }
        if((*b)->type == DQUOTE)
        {   
            str = ft_strjoin(str, expand_dollar((*b)->val));
        }
        else if((*b)->type != END)
        {   
            str = ft_strjoin(str, (*b)->val);
        }
        if((*b)->flag == 1)
            (*b) = (*b)->next;
        else
        {
            (*b) = (*b)->next;
            return str;
        }
	}
    if((*b)  && (*b)->type == DOLLAR)
    {
        if(!(*b)->val[1])
        {
            (*b) = (*b)->next;
            if(getenv((*b)->val))
                    (*b)->val = getenv((*b)->val);
                else
                    (*b)->val = strdup("");
        }
        else
        {
            if((*b)->val[1] == ' ')
                str = ft_strjoin(str, strdup("$"));
            (*b) = (*b)->next;
            return str;
        }
    }
    if((*b)  && (*b)->type == DQUOTE)
    {   
        str = ft_strjoin(str, expand_dollar((*b)->val));
        (*b) = (*b)->next;
    }
    else if((*b)  && (*b)->type != END)
    {   
        str = ft_strjoin(str, (*b)->val);
        (*b) = (*b)->next;
    }
    return str;
}

void    *realloc_array(char **arg, char *str)
{
    int i;
    int j;
    char **new_arg;

    i = 0;
    j = 0;
    while (arg && arg[i])
        i++;
    new_arg = (char **)malloc(sizeof(char *) * (i + 2));
    while (arg && j < i)
    {
        new_arg[j] = ft_strdup(arg[j]);
        j++;
    }
    new_arg[j++] = ft_strdup(str);
    new_arg[j] = NULL;
    return (new_arg);
}
