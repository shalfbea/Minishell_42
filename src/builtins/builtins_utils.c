/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:11:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/20 15:35:14 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(void)
{
	g_ms_env.builtin_names[0] = "echo";
	g_ms_env.builtin_names[1] = "cd";
	g_ms_env.builtin_names[2] = "pwd";
	g_ms_env.builtin_names[3] = "export";
	g_ms_env.builtin_names[4] = "unset";
	g_ms_env.builtin_names[5] = "env";
	g_ms_env.builtin_names[6] = "exit";
	g_ms_env.builtin_functions[0] = ft_echo;
	g_ms_env.builtin_functions[1] = ft_cd;
	g_ms_env.builtin_functions[2] = ft_pwd;
	g_ms_env.builtin_functions[3] = ft_export;
	g_ms_env.builtin_functions[4] = ft_unset;
	g_ms_env.builtin_functions[5] = ft_env;
	g_ms_env.builtin_functions[6] = ft_exit;
}

int	check_builtin(char *name)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(g_ms_env.builtin_names[i], name, ft_strlen(g_ms_env.builtin_names[i]) + 1))
			return (i);
		i++;
	}
	return (i);
}

int	run_builtin(t_command_list *cmd, t_exec_env *in_exec)
{
	int		num;

	in_exec = NULL;//fix it !!!!!!!!!!!!!!!!!!!!!
	num = check_builtin(cmd->argv[0]);
	g_ms_env.ex_code = g_ms_env.builtin_functions[num](cmd->argv);
	return (g_ms_env.ex_code);
}
