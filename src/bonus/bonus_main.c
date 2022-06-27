/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:17:20 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/27 20:57:17 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_environment	g_ms_env;

static int	c_argument_support(int argc, char **argv)
{
	t_list			*raw_lexer_data;
	t_list			*groups;

	if (argc < 3)
		return (0);
	if (ft_strncmp(argv[1], "-c", 2))
		return (0);
	g_ms_env.prompt_mode = 1;
	raw_lexer_data = prompt(argv[2]);
	g_ms_env.prompt_mode = 0;
	groups = to_polish_notation(raw_lexer_data);
	if (S_DEBUG)
		debug_groups_printer(groups);
	if (groups)
		groups_executor(groups);
	clear_lexer_lst(&(raw_lexer_data));
	return (SHELL_CLOSE);
}

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
	executor_result = c_argument_support(argc, envp);
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
		ft_lstclear(&groups, group_free);
	}
	string_array_cleaner(&g_ms_env.envp);
	exit(0);
}
