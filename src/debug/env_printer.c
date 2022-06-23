/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:06:55 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:07:05 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_ms_env_printer(void)
{
	int	i;

	i = -1;
	printf("envp: \n");
	if (!g_ms_env.envp)
		printf("NULL\n");
	while (g_ms_env.envp[++i])
		printf("%s\n", g_ms_env.envp[i]);
	printf("\nExit code: %d\n", g_ms_env.ex_code);
	printf("Number of commands: %d\n", g_ms_env.number_of_commands);
	i = -1;
	if (g_ms_env.pids)
	{
		printf("pids: \n");
		while (g_ms_env.pids[++i])
		{
			printf("%d", g_ms_env.pids[i]);
			if (g_ms_env.pids[i + 1])
				printf(", ");
		}
		printf("\n");
	}
	else
		printf("Pids not presented.\n");
}
