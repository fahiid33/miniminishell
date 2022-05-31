/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/05/31 03:55:09 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	add_string_to_env(t_env *env, char *to_add)
{
	char   **str;
	char  *tmp;
	int   i = 0;
	int	j = 0;
	int index;
	int size = array_size(env->env);
	tmp = ft_substr(to_add, 0, ft_int_strchr(to_add, '=') + 1);
	index = my_i_getenv(tmp, env->env);
	if (index)
	{
		
		tmp = env->env[index];
		env->env[index] = to_add;
		free(tmp);
	}
	else
	{
		str = (char **)malloc(sizeof (char *) * (size + 1));
		while (env->env[i])
		{
			str[j] = strdup(env->env[i]);
			i++; 
			j++; 
		}
		str[j] = strdup(to_add);
		str[++j] = NULL;
		env->env = str;
	}
	// printf("str ==-%s\n",str[j - 1]);
	// // printf("to_add ===%s\n", to_add);
	// str[++j] = NULL;
}

void	add_string_to_export(t_env *env, char *to_add) //var=19 // var1=
{
	char   **str;
	char  *tmp;
	int   i = 0;
	int	j = 0;
	int y;
	int index;
	int size = array_size(env->export);
	y = ft_int_strchr(to_add, '=');
	if(y == -1)
		y = ft_int_strchr(to_add, '\0');
	tmp = ft_substr(to_add, 0, y);
	printf("%s\n",tmp);
	index = my_i_getexp(tmp , env->export);
	printf("%d\n",index);
	if (index)
	{
		if(ft_int_strchr(env->export[index], '=') != -1)
			tmp = ft_substr(env->export[index],0,ft_int_strchr(env->export[index], '=')+1);
		else
		{
			tmp = ft_substr(env->export[index],0,ft_int_strchr(env->export[index], '\0'));
			tmp = ft_strjoin(tmp,"=",0);
		}
		if (ft_int_strchr(to_add, '=') != -1)
		{
			tmp = ft_strjoin(tmp, "\"",0);
			tmp = ft_strjoin(tmp,ft_substr(to_add,ft_int_strchr(to_add, '=')+1, strlen(to_add)),2);
			to_add = ft_strjoin(tmp ,"\"",0);
			env->export[index] = to_add;
		}
	}
	else
	{
		str = (char **)malloc(sizeof (char *) * (size + 1));
		while (env->export[i])
		{
			str[j] = strdup(env->export[i]);
			i++; 
			j++; 
		}
		to_add = ft_strjoin("declare -x ", to_add,1);
		if (ft_int_strchr(to_add, '=') != -1)
		{
			tmp = ft_substr(to_add,0,ft_int_strchr(to_add, '=')+1);
			tmp = ft_strjoin(tmp, "\"",0);
			tmp = ft_strjoin(tmp,ft_substr(to_add,ft_int_strchr(to_add, '=')+1, strlen(to_add)),2);
			to_add = ft_strjoin(tmp ,"\"",0);
		}
		str[j] = strdup(to_add);
		str[++j] = NULL;
		env->export = str;
	}
	// printf("str ==-%s\n",str[j - 1]);
	// // printf("to_add ===%s\n", to_add);
	// str[++j] = NULL;
}

char **get_string(char **env)
{
	char **str;
	int i;
	char *tmp;
	i = 0;
   while(env[i++])
	str = malloc(sizeof(char *) * i + 1);
   i = 0;
	while(env[i])
	{
		str[i] = ft_strdup((tmp = ft_substr(env[i] , 0, '=')));
		free(tmp);
		i++;
	}
	str[i++] = NULL;
	return(str);
}

char** init_export(char **env)
{
	char *s1;
	char **strings;
	int		i;
	int		j;
	char **res;
	char *tmp;
	j = 0;
	s1 = ft_strdup("");
	// free_l(strings);

	i = 0;
   
	while(env[i])
	{
		s1 = ft_strjoin(s1,"declare -x ",0);
		s1 = ft_strjoin(s1,ft_substr(env[i], 0, ft_int_strchr(env[i], '=') + 1),2);
		
		s1 = ft_strjoin(s1,"\"",0);
		s1 = ft_strjoin(s1,strchr(env[j],'=')+ 1,0);
		s1 = ft_strjoin(s1,"\"\n",0);
		if(strncmp(env[i] , "PWD",3) == 0)
		{
			i++;
			s1 = ft_strjoin(s1,"declare -x OLDPWD\n",0);
		}
		j++;
		i++;
	}

//    system("leaks minishell");
//     exit(0);
   res = ft_split(s1,'\n');
   return res;
}


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
			add_string_to_env(my_env, ft_strjoin("PWD=",strdup(pwd(head, 0)),1));
			add_string_to_export(my_env, ft_strjoin("PWD=",pwd(head, 0),-1));
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
	char *buf;
	char *dir;
	size_t size;

	size = PATH_MAX;
	buf = (char *)malloc(sizeof(size_t));
	if (!head->argv[0] && !strcmp(head->cmd, "pwd"))
	{
		dir = getcwd(buf, size);
		printf("%s\n", dir);
	}
	else
	{
		if (k)
		{
			printf("pwd: too many arguments\n");
		}
		dir = getcwd(buf, size);
		// printf("%lu\n", strlen(dir));
	}
	return(dir);
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
	int i=0;
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
int	my_i_getenv(char *str, char **my_env) //var=
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		if (strncmp(str, my_env[i], strlen(ft_substr(my_env[i], 0 , ft_int_strchr(my_env[i], '=')))) == 0)
			return (i);
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

void builtins(t_parse *commands, t_env *env)
{
	t_parse *head;

	head = commands;
	head->argv++;
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
	}
	head->argv--;
}