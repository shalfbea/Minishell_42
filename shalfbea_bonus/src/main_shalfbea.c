/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shalfbea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/24 19:22:58 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int
	(void ) argc;
	(void ) argv;
	(void ) envp;
	commands = NULL;
	int debug = 1;
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	while (1)
	{
		if (debug)
			debug_ms_env_printer();
		raw_lexer_data = prompt(NULL, debug);
		commands = get_command(raw_lexer_data, debug);
		if (debug)
			printf("Number of commands: %d\n", g_ms_env.number_of_commands);
		if (!commands)
			return (0);
	}
	return (0);
}
