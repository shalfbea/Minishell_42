/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shalfbea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/19 19:43:37 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;

	(void ) argc;
	(void ) argv;
	(void ) envp;
	commands = NULL;
	int debug = 1;
	while (1)
	{
		commands = prompt(NULL, debug);
		if (debug)
			printf("Number of commands: %d\n", ms_env.number_of_commands);
		if (!commands)
			return (0);
	}
	return (0);
}
