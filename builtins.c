/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/07/30 19:36:40 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void print_list(t_token *lst)
// {
//    while (lst)
//    {
//       printf("value == %s --------  type: %d --------  flag: %d \n", lst->val, lst->type, lst->flag);
//       lst = lst->next;
//    }
// }

// void print_l(t_parse *lst)
// {
//    int i;
//    while (lst)
//    {
//       i  =0;
//       if (lst->cmd)
//       {
//          printf("cmd == %s --------  args: ", lst->cmd);
//          while(lst->argv && lst->argv[i])
//          {
//             printf("<<<%s>>",lst->argv[i]);
//             i++;
//          }
//          if (lst->next->next)
//             printf("  | \n");
//          else
//             printf("\n");
//       }
//       lst = lst->next;
//    }
// }

// int array_size(char **str)
// {
// 	int i = 0;
// 	while (str[i])
// 		i++;
// 	// printf("%d\n", i);
// 	return (i);
// }

int	builtins_cases(t_parse *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp(cmd->cmd, "unset") || !ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

int  exec_builtins(t_parse *head, t_env **my_env)
{
	
	head->argv++;
	if (!strcmp(head->cmd, "cd"))
		return(cd(head, (*my_env)));
	else if (!strcmp(head->cmd, "env") || !strcmp(head->cmd, "ENV"))
		return (env());
	else if (!strcmp(head->cmd, "export"))
		return(export(head));
	else if (!strcmp(head->cmd, "pwd") || !strcmp(head->cmd, "PWD"))
		return(pwd());
	else if (strcmp(head->cmd, "exit") == 0)
		return(my_exit(head));
	else if (!strcmp(head->cmd, "echo") || !strcmp(head->cmd, "ECHO"))
		return(echo(head));
	else if (!strcmp(head->cmd, "unset"))
		return(unset(head));
	head->argv--;
    return(0);
}



