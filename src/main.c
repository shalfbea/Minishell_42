/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/24 19:46:58 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int				executor_result;

	(void ) argc;
	(void ) argv;
	(void ) envp;
	commands = NULL;
	int debug = 0;
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	while (1)
	{
		//if (debug)
		//	debug_ms_env_printer();
		raw_lexer_data = prompt(NULL, debug);
		commands = get_command(raw_lexer_data, debug);
		if (!commands)
			break ;
		executor_result = executor(commands);
		//clear_command_lst(&commands);
	}
	string_array_cleaner(&g_ms_env.envp);
	return (0);
}
