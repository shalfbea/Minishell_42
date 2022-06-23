/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 21:09:18 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_environment g_ms_env;

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
	executor_result = 0;
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
	}
	string_array_cleaner(&g_ms_env.envp);
	//return (g_ms_env.ex_code);
	return (g_ms_env.ex_code);
}
