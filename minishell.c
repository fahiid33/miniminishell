/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/06/20 07:33:44 by fahd             ###   ########.fr       */
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

char	**my_envir(char **env)
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
void  print_list_env(t_env *tmp)
{
//  printf every node in env list
 if (tmp)
 {
   while (tmp)
    {
        if (tmp->sep)
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putchar_fd(tmp->sep, 1);
            if (tmp->val == NULL)
                ft_putchar_fd('\n', 1);
            else
            {
                ft_putstr_fd(tmp->val, 1);
                  ft_putchar_fd('\n', 1);
            }
        }
        tmp = tmp->next;
    }
 }
}

int main(int ac, char *av[], char **env)
{
   // char	*line;
   t_parse *commands;
   t_lexer	*test;
   t_token *test1;
   (void)ac;
   (void)av;
   (void)env;
   //    // dup2(pipefd[1], 1);
   // //  pipe(pipefd);
   // // printf_env(my_export);
   // // printf("sec address === %p\n\n", my_env.env[14]);
	   
   g_vars.my_env = init_env(env);
   // printf("%s\n\n", g_vars.my_env->key);
   // print_list_env(g_vars.my_env);
   // exit(0);
   while (1)
   {
         c_signal();
      g_vars.line = readline("MESSI-1.0$ ");
         if (!g_vars.line)
         {
            printf("exit\n");
            exit(g_vars.exit_status);
         }
         if (g_vars.line[0] == '\0')
         {
            free(g_vars.line);
            continue;
         }
         commands = init_command();
         test = malloc(sizeof(t_lexer));
         test = ft_init_lexer(g_vars.line, g_vars.line[0]);
         test1 = send_lexer_to_tokenize(test);//tokenizing every char in the line
         add_history(g_vars.line);
         create_commands(test1, &commands);
         if (!g_vars.g_err)
            exec_pipeline(commands, &g_vars.my_env);
   }

}
