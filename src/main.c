/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/27 20:25:01 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_environment g_ms_env;

static int	c_argument_support(int argc, char **argv)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;

	if (argc < 3)
		return (0);
	if (ft_strncmp(argv[1], "-c", 2))
		return (0);
	g_ms_env.prompt_mode = 1;
	raw_lexer_data = prompt(argv[2]);
	g_ms_env.prompt_mode = 0;
	commands = get_command(raw_lexer_data);
	executor(commands);
	clear_lexer_lst(&(raw_lexer_data));
	return (SHELL_CLOSE);
}

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int				executor_result;

	(void) argc;
	(void) argv;
	rl_outstream = stderr; //ONLY 4 testing
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	//debug_set_envp(); // Delete
	executor_result = c_argument_support(argc, argv);// 0;
	while (executor_result != SHELL_CLOSE)
	{
		g_ms_env.prompt_mode = 1;
		raw_lexer_data = prompt(NULL);
		g_ms_env.prompt_mode = 0;
		commands = get_command(raw_lexer_data);
		if (!commands) // ONLY DEBUG
			break ;
		executor_result = executor(commands);
		clear_lexer_lst(&(raw_lexer_data));
		if (S_DEBUG == 1)
			executor_result = SHELL_CLOSE;
	}
	string_array_cleaner(&g_ms_env.envp);
	//pause();
	return (g_ms_env.ex_code);
}
