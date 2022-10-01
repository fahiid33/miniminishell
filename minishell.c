/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/10/01 06:57:21 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_vars.exit_status);
}

t_token	*parse_cmd(t_token *tokens)
{
	t_lexer	*lexer;
	
	lexer = NULL;
	// lexer = f_malloc(sizeof(t_lexer));
	lexer = ft_init_lexer(g_vars.line, g_vars.line[0]);
	tokens = send_lexer_to_tokenize(lexer);
	return (tokens);
}

void	init_gs_and_c_signal(void)
{
	
	g_vars.line = NULL;
	g_vars.exit_sig = 0;
	g_vars.g_err = 0;
	c_signal();
}

void	mino(t_parse *cmds)
{
	if (!g_vars.g_err)
	{
		read_heredocs(cmds);
		if (g_vars.exit_sig != -27)
			exec_pipeline(cmds, &g_vars.my_env);
	}
}

void	freeha()
{
	// int	i;

	// i = 0;
	// if (cmds)
	// {
	// 	while(cmds)
	// 	{
	// 		if (cmds->cmd)
	// 			free(cmds->cmd);
	// 		if (cmds->argv)
	// 		{
	// 			while (cmds->argv[i])
	// 			{
	// 				if (cmds->argv[i])
	// 				{
	// 					free(cmds->argv[i]);
	// 				}
	// 				i++;
	// 			}
	// 		}
	// 		if (cmds->redir && cmds->redir->file)
	// 			// printf("%s\n", cmds->redir->file);
	// 			free(cmds->redir->file);
	// 		if (cmds->redir)
	// 			free(cmds->redir);
	// 		// while(1);
	// 		// free(cmds);
	// 		// while(1);
	// 		cmds = cmds->next;
			
	// 	}
	// 	// while(1);
	// }
	int	i;

	i = 0;
	while(i < g_vars.i)
	{
		if (g_vars.alloc[i])
			free(g_vars.alloc[i]);
		i++;
	}
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*commands;
	t_token	*tokens;

	commands = NULL;
	tokens = NULL;
	(void)ac;
	(void)av;
	init_env(env);
	// int i = 0;
	g_vars.i = 0;
	while (1)
	{
		init_gs_and_c_signal();
		g_vars.line = readline("missi-1.0$ ");
		if (!g_vars.line)
			exit_shell();
		if (only_enter())
			continue ;
		commands = init_command();
		tokens = parse_cmd(tokens);
		create_commands(tokens,	 &commands);
		add_history(g_vars.line);
		mino(commands);
		free(g_vars.line);
		// freeha();
		// i++;
	}
}
