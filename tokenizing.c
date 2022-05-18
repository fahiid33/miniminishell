/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:26:06 by fahd              #+#    #+#             */
/*   Updated: 2022/05/18 20:32:53 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *init_token(char *val, int type)
{
    t_token *token;

    if (!(token = (t_token *)malloc(sizeof(t_token))))
        return (NULL);
    token->val = val;
    token->next = NULL;
    token->type = type;
    return (token);
}
