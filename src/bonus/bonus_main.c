/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:17:20 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/24 17:41:05 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_environment	g_ms_env;

int	main(int argc, char **argv, char **envp)
{
	t_list			*raw_lexer_data;
	int				executor_result;
	t_list			*groups;

	(void) argc;
	(void) argv;
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	executor_result = 0;
	while (executor_result != SHELL_CLOSE)
	{
		g_ms_env.prompt_mode = 1;
		raw_lexer_data = prompt(NULL);
		g_ms_env.prompt_mode = 0;
		groups = to_polish_notation(raw_lexer_data);
		if (S_DEBUG)
			debug_groups_printer(groups);
		if (groups)
			executor_result = groups_executor(groups);
		clear_lexer_lst(&(raw_lexer_data));
	}
	string_array_cleaner(&g_ms_env.envp);
	exit(0);
}
