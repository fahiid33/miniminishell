/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/21 04:37:30 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(t_token *lst)
{
   while (lst)
   {
      printf("value == %s --------  type: %d --------  flag: %d \n", lst->val, lst->type, lst->flag);
      lst = lst->next;
   }
}
void print_l(t_parse *lst)
{
   int i;
   while (lst)
   {
      i  =0;
      if (lst->cmd)
      {
         printf("cmd == %s --------  args: ", lst->cmd);
         while(lst->argv && lst->argv[i])
         {
            printf("---%s----",lst->argv[i]);
            i++;
         }
         if (lst->next->next)
            printf("  | \n");
         else
            printf("\n");
      }
      lst = lst->next;
   }
}
int main(int ac, char *av[], char **env)
{
   char	*line;
   char	*l;
   int	i = 0;
   t_parse *commands;


      t_lexer	*test;
      t_token *test1;
   while((line = readline("Minishell ")))
   {
      commands = init_command();
      test = malloc(sizeof(t_lexer));
      test = ft_init_lexer(line, line[0]);//initilize the lexer
      test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
      add_history(line);
      create_commands(test1, &commands);
      // print_list(test1);
      print_l(commands);
   }
   
}