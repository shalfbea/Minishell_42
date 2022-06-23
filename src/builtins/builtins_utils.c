/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:11:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/23 14:30:01 by cbridget         ###   ########.fr       */
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
	if (!name)
		return (100);
	while (i < NUM_BULTINS)
	{
		if (!ft_strncmp(g_ms_env.builtin_names[i], name, \
			ft_strlen(g_ms_env.builtin_names[i]) + 1))
			return (i);
		i++;
	}
	return (i);
}

int	run_builtin(t_command_list *cmd, t_exec_env *in_exec, int num)
{
	int		n_cmd;
	int		save[2];

	n_cmd = check_builtin(cmd->argv[0]);
	if (working_with_redirects(cmd, in_exec, num))
	{
		if (g_ms_env.number_of_commands == 1)
		{
			in_exec->first_fd->r_code = g_ms_env.ex_code;
			return (0);
		}
		return (1);
	}
	swap_filedescriptors(in_exec, num, save);
	if (n_cmd == 6)
		return (run_builtin_02(cmd, in_exec, num, save));
	else
		return (run_builtin_03(cmd, in_exec, num, save));
}

int	run_builtin_03(t_command_list *cmd, t_exec_env *in_exec, int num, int *save)
{
	g_ms_env.ex_code = \
	g_ms_env.builtin_functions[check_builtin(cmd->argv[0])](cmd->argv);
	retrieve_filedescriptors(in_exec, num, save);
	if (g_ms_env.number_of_commands == 1)
	{
		in_exec->first_fd->r_code = g_ms_env.ex_code;
		return (0);
	}
	return (g_ms_env.ex_code);
}

int	run_builtin_02(t_command_list *cmd, t_exec_env *in_exec, int num, int *save)
{
	int	n_cmd;

	n_cmd = check_builtin(cmd->argv[0]);
	n_cmd = g_ms_env.builtin_functions[n_cmd](cmd->argv);
	retrieve_filedescriptors(in_exec, num, save);
	if (g_ms_env.number_of_commands == 1)
	{
		if (n_cmd == SHELL_CLOSE)
			return (n_cmd);
		in_exec->first_fd->r_code = 1;
		return (0);
	}
	else
		return (g_ms_env.ex_code);
}
