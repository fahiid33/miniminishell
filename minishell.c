/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/29 07:18:51 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, unsigned int n)
{
	char				*new;
	unsigned int		i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	while (i < n)
		new[i++] = *str++;
	new[n] = 0;
	return (new);
}
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
         printf("cmd == %s args: ", lst->cmd);
         while(lst->argv && lst->argv[i])
         {
            printf("||||%s||||",lst->argv[i]);
            i++;
         }
         printf(" files: ");
         while(lst->redir)
         {
            printf("%d - %s ; ", lst->redir->type,lst->redir->file);
            lst->redir = lst->redir->next;
         }
         if (lst->next->next)
            printf("  | \n");
         else
            printf("\n");
      }
      lst = lst->next;
   }
}
char	*str_join(char *s1, char *s2)
{
	char	*copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char) * (ft_int_strchr(s1, 0) + ft_int_strchr(s2, 0) + 2));
	i = 0;
	j = 0;
	while (s1[j])
		copy[i++] = s1[j++];
	copy[i++] = '/';
	j = 0;
	while (s2[j])
		copy[i++] = s2[j++];
	copy[i] = 0;
	return (copy);
}


char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && ft_int_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_int_strchr(path, ':'));
		bin = str_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_int_strchr(path, ':') + 1;
	}
	return (cmd);
}

// char* expand_dollar(char *str);

int main(int ac, char *av[], char **env)
{
   char	*line;
   char	*l;
   int	i = 0;
   int   pipefd[2];
   t_parse *commands;


      t_lexer	*test;
      t_token *test1;
      char *path;
      int pid ;
      // dup2(pipefd[1], 1);
      pipe(pipefd);
   while((line = readline("Bash$ ")))
   {
      commands = init_command();
      test = malloc(sizeof(t_lexer));
      test = ft_init_lexer(line, line[0]);//initilize the lexer
      test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
      add_history(line);
      create_commands(test1, &commands);
      // printf("----------------------\n");
      path = get_path(commands->cmd, env);
      
      pid = fork();
      if(pid)
      {
         close(pipefd[1]);
         dup2(pipefd[0], 0);
         waitpid(pid, NULL, 0);
         
         
      }
      else
      {
         close(pipefd[0]);
         dup2(pipefd[1], 1);
         execv(path, commands->argv);
         printf("command not found : %s\n", commands->cmd);
         exit(127);
      }
      commands = commands->next;
      path = get_path(commands->cmd, env);
      execv(path, commands->argv);
      
      
      // printf("hdfjeocfjkwkjdkejwkmdkmwekdmfcklewmdk\n\n");
      // print_l(commands);
   }

}
