/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/06/05 18:09:49 by aainhaja         ###   ########.fr       */
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

void cd(t_parse *head, t_env *my_env)
{
	char *ha;
	ha = ft_strjoin("OLDPWD=",strdup(pwd(head, 0)),1);
	add_string_to_env(my_env, ha);
	if (!head->argv[0] || !strcmp(head->argv[0],"~"))
	{
		add_string_to_export(my_env, ft_strjoin("OLDPWD=",strdup(pwd(head, 0)),1));
		chdir(getenv("HOME"));
		add_string_to_env(my_env, ft_strjoin("PWD=",strdup(pwd(head, 0)),1));
		add_string_to_export(my_env, ft_strjoin("PWD=",pwd(head, 0),-1));
	}
	else if (head->argv[0] && !head->argv[1])
	{
		add_string_to_export(my_env, ft_strjoin("OLDPWD=",strdup(pwd(head, 0)),1));
		if (chdir(head->argv[0]) == -1)
			printf("cd: no such file or directory: %s \n", head->argv[0]);
		else
		{
			ha = strdup(pwd(head, 0));
			add_string_to_env(my_env, ft_strjoin("PWD=", ha, -1));
			add_string_to_export(my_env, ft_strjoin("PWD=",ha, 1));
		}
	}
	else
		printf("cd: too many arguments\n");
}

void printf_env(char **lenv)
{
	int i;

	i = 0;
	while (lenv[i])
	{
		printf("%s\n", lenv[i]);
		i++;
	}
	// exit (0);
}

char *pwd(t_parse *head, int k)
{
	char *dir;

	if (!head->argv[0] && !strcmp(head->cmd, "pwd"))
	{
		dir = getcwd(NULL, 0);
		printf("%s\n", dir);
		k = 1;
	}
	else
	{
		if (!k && !strcmp(head->cmd, "pwd"))
			printf("pwd: too many arguments\n");
		dir = getcwd(NULL, 0);
	}
	return (dir);
}

int	perr_exp(char *str)
{
	int	i;
	i = 0;
	while(str && str[i]&& str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
		{
			printf("bash: export: %s : not a valid identifier \n", ft_substr(str, 0, ft_int_strchr(str, '=')));
			return (1);
		}
		i++;
	}
	return(0);
}
char **add_export(t_parse *head, t_env *env)
{
	int	i;

	i = 0;
	while(head->argv[i])
	{
		// if(perr_exp(strdup(head->argv[i])))
		// 	break;
		if (head->argv[i] && ft_int_strchr(head->argv[i], '=') != -1)
		{
			add_string_to_env(env, head->argv[i]);
			add_string_to_export(env,head->argv[i] );
		}
		else if (head->argv[i] && ft_int_strchr(head->argv[i], '=') == -1)
		{
			add_string_to_export(env, head->argv[i]);
		}
		i++;
	}
	if(!head->argv[0])
		printf_env(env->export);
	// exit (0);
	return (env->export);
}

void	check_numb(char *str)
{
	int	i;

	i = 0;	
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", str);			
			exit(0);
		}
		i++;
	}
}

void my_exit(t_parse *cmd)
{
	int j;

	j = 0;
	if (cmd->argv[0])
	{
		if (!strcmp(cmd->argv[0], "0"))
		{
			printf("exit\n");
			exit(0);
		}
		check_numb(cmd->argv[0]);
		if (cmd->argv[1])
		{
			printf("exit\n");
			printf("bash: exit: too many arguments\n");
		}
		else
		{
			printf("exit\n");
			exit(1);
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
void echo(t_parse *cmd)
{
	int i;

	i = 1;
	// if (!cmd->argv && !cmd->argv[0])
	// 	write(1, "\n", 1);
	if (cmd->argv)
	{
		if (strcmp(cmd->argv[0], "-n") == 0)
		{
			while (cmd->argv[i])
			{
				write(1, cmd->argv[i], strlen(cmd->argv[i]));
				i++;
			}
		}
		else
		{
			i = 0;
			while (cmd->argv[i])
			{
				write(1, cmd->argv[i], strlen(cmd->argv[i]));
				i++;
			}
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	// exit (0);
}

void	del_2d_array(char *arg, t_env env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env.env[i] && strncmp(arg, env.env[i], strlen(arg)))
		i++;
	while (env.env[i])
	{
		if (env.env[i + 1])
			env.env[i] = strdup(env.env[i + 1]);
		else
			env.env[i] = NULL;
		i++;
	}
	while (env.export[j] && strncmp(arg, ft_substr(env.export[j],ft_int_strchr(env.export[j],' ') + 4,ft_int_strchr(env.export[j],'=')),strlen(arg)))
		j++;	
	while (env.export[j])
	{
		if (env.export[j + 1])
			env.export[j] = strdup(env.export[j + 1]);
		else
			env.export[j] = NULL;
		j++;
	}
}
char	*my_getenv(char *str, char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		if (strncmp(str, my_env[i], strlen(str)))
			return (ft_substr(my_env[i], strlen(str), strlen(my_env[i])));
		i++;
	}
	return (NULL);
}
int	my_i_getenv(char *str, char **my_env) //PWD=
{
	int	i;

	i = 0;
	// printf("to_add==%s\n\n", str);
	while (my_env[i])
	{
		if (strncmp(str, my_env[i], ft_int_strchr(my_env[i], '=')) == 0)
		{
			return (i);	
		}
		i++;
	}
	return (0);
}

int	my_i_getexp(char *str, char **my_exp) //var=
{
	int	i;

	i = 0;
	while (my_exp[i])
	{
		if(ft_int_strchr(ft_strchr(my_exp[i],'x'), '=') - 2 > 0)
		{
			if (strcmp(str, ft_substr(my_exp[i], 11, ft_int_strchr(ft_strchr(my_exp[i],'x'), '=') - 2)) == 0)
				return (i);
		}
		else if (strcmp(str, ft_substr(my_exp[i], 11, ft_int_strchr(ft_strchr(my_exp[i],'x'), '\0') - 2)) == 0)
				return (i);
		i++;
	}
	return (0);
}
void	unset(t_parse *cmd, t_env env)
{
	int i ;

	i = 0;
	// printf("var===%s\n",cmd->argv[i]);
	if (!cmd->argv)
		return ;
	while (cmd->argv[i])
	{
		if (my_getenv(cmd->argv[i], env.env))
			del_2d_array(cmd->argv[i], env);
		i++;
	}
	// exit (0);
}

void builtins(t_parse *commands, t_env *env, char *line)
{
	t_parse *head;

	head = commands;
	head->argv++;
	int pid;
	int fd[2];
	char *path;
	char **ok;
	//  printf("--%s--" ,head->argv[0]);
	//  printf("sec address === %p\n\n", env.env[14]);
	if (head)
	{
		// printf("--%s--" ,head->cmd);
		if (strcmp(head->cmd, "cd") == 0)
			cd(head, env);
		else if (strcmp(head->cmd, "env") == 0)
			printf_env(env->env);
		else if (strcmp(head->cmd, "export") == 0)
		{
			// perror("rgjdgkvkr\n\n\n\n");
			add_export(head, env);
			// exit(0);
		}
		else if (strcmp(head->cmd, "pwd") == 0)
		{
			pwd(head, 0);
						// exit (0);
		}
		else if (strcmp(head->cmd, "exit") == 0)
			my_exit(head);
		else if (strcmp(head->cmd, "echo") == 0)
			echo(head);
		else if (strcmp(head->cmd, "unset") == 0)
		    unset(head, *env);
		else
		{
			while(head->next->next != NULL)
			{
				pipe(fd);
					pid = fork();
				if(pid)
      			{
      			   close(fd[1]);
      			   dup2(fd[0], 0);
      			   waitpid(pid, NULL, 0);
      			}
      			else
      			{
					close(fd[0]);
					dup2(fd[1], 1);
      				execute(head->cmd, env->env);
      			}
				  head = head->next;
			}
			if(head->next != NULL)
				execute(head->cmd, env->env);
		}
	}
	head->argv--;
}

void	execute(char *command, char **env)
{
	char	**ac;
	char	*path;

	if (command[0] != '\0')
		ac = ft_split(command, ' ');
	else
	{
		printf("aaaa");
		exit(127);
	}
	path = get_path(ac[0], env);
	execve(path, ac, env);
}