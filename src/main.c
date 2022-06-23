/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 17:34:04 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_environment g_ms_env;

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int				executor_result;

	(void ) argc;
	(void ) argv;
	(void ) envp;
	commands = NULL;
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	while (1)
	{
		g_ms_env.prompt_mode = 1;
		raw_lexer_data = prompt(NULL);
		g_ms_env.prompt_mode = 0;
		commands = get_command(raw_lexer_data);
		if (!commands) // ONLY DEBUG
			break ;
		executor_result = executor(commands);
		clear_lexer_lst(&(raw_lexer_data));
		(void) executor_result;
		//clear_command_lst(&commands);
	}
	string_array_cleaner(&g_ms_env.envp);
	return (0);
}
