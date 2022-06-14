/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/06/14 02:01:00 by fstitou          ###   ########.fr       */
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
	if (!head->argv[0] || !strcmp(head->argv[0],"~") || head->argv[0][0] == '\0')
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

char **add_export(t_parse *head, t_env *env,int fd)
{
	int	i;

	i = 0;
	while(head->argv[i])
	{
		if (head->argv[i] && ft_int_strchr(head->argv[i], '=') != -1)
		{
			add_string_to_env(env, head->argv[i]);
			add_string_to_export(env,head->argv[i]);
		}
		else if (head->argv[i] && ft_int_strchr(head->argv[i], '=') == -1)
		{
			add_string_to_export(env, head->argv[i]);
		}
		i++;
	}
	if(!head->argv[0] && fd == 0)
	{
		printf("gaaaa\n");
		printf_env(env->export);
	}
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
			perror("exit\n");
			exit(0);
		}
		check_numb(cmd->argv[0]);
		if (cmd->argv[1])
		{
			perror("exit\n");
			perror("bash: exit: too many arguments\n");
		}
		else
		{
			perror("exit\n");
			exit(1);
		}
	}
	else
	{
		perror("exit\n");
		exit(EXIT_SUCCESS);
	}
}
void echo(t_parse *cmd, int fd)
{
	int i;

	i = 1;
	if (cmd->argv && cmd->argv[0])
	{
		if (strcmp(cmd->argv[0], "-n") == 0)
		{
			while (cmd->argv[i])
			{
				write(fd, cmd->argv[i], strlen(cmd->argv[i]));
				write(fd, " ", 1);
				i++;
			}
		}
		else
		{
			i = 0;
			while (cmd->argv[i])
			{
				write(fd, cmd->argv[i], strlen(cmd->argv[i]));
				write(fd, " ", 1);
				i++;
			}
			write(fd, "\n", 1);
		}
	}
	else
		write(fd, "\n", 1);
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
