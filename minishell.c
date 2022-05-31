/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/05/31 03:44:02 by fstitou          ###   ########.fr       */
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
            printf("%s  ",lst->argv[i]);
            i++;
         }
         
         while(lst->redir)
         {
            printf(" redir => ");
            printf("%s ; ", lst->redir->file);
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
int array_size(char **str)
{
	int i = 0;
	while (str[i])
		i++;
	// printf("%d\n", i);
	return (i);
}

char  **my_envir(char **env)
{
   char   **str;
   int   i = 0;
   int	j = 0;
   int size = array_size(env);
   if(getenv("OLDPWD") != NULL)
      str = (char **)malloc(sizeof (char *) * (size));
   else
      str = (char **)malloc(sizeof (char *) * (size + 1));
	while (env[i])
	{
      if(strncmp(env[i],"OLDPWD",6))
		{
         str[j] = strdup(env[i]);
		   j++;
      }
		i++;
	}
	str[j] = NULL;
	return (str); 
}
void  free_l(char **env)
{
   int i;
   for (i = 0; env[i]; i++)
		free(env[i]);
	free(env[i]);
}
// char* expand_dollar(char *str);

int main(int ac, char *av[], char **env)
{
   char	*line;
   char	*l;
   int	i = 0;
   int   pipefd[2];
   t_env *my_env;
   t_parse *commands;


      t_lexer	*test;
      t_token *test1;
      char *path;
      int pid ;
   char **my_export;
      // dup2(pipefd[1], 1);
      pipe(pipefd);
   my_env = malloc(sizeof(t_env));
   // printf_env(my_export);
   // printf("sec address === %p\n\n", my_env.env[14]);
	   
      my_env->env = my_envir(env);
      my_env->export = init_export(my_env->env);
   while((line = readline("MESSI-1.0$ ")))
   {
      commands = init_command();
      test = malloc(sizeof(t_lexer));
      test = ft_init_lexer(line, line[0]);//initilize the lexer
      test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
      add_history(line);
      create_commands(test1, &commands);

      // printf("----------------------\n");
      path = get_path(commands->cmd, env);
      
      // print_l(commands);
      builtins(commands, my_env);
      //  system("leaks minishell");
      // exit(0);
      // pid = fork();
      // if(pid)
      // {
      //    // close(pipefd[1]);
      //    // dup2(pipefd[0], 0);
      //    waitpid(pid, NULL, 0);
         
         
      // }
      // else
      // {
      //    // close(pipefd[0]);
      //    // dup2(pipefd[1], 1);
      //    execv(path, commands->argv);
      //    printf("command not found : %s\n", commands->cmd);
      //    exit(127);
      // }
      // commands = commands->next;
      // path = get_path(commands->cmd, env);
      // execv(path, commands->argv);
      
   
   }
}
