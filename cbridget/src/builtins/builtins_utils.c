/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:11:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/16 22:15:41 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(t_minishell_environment *m_env)
{
	m_env->builtin_names[0] = "echo";
	m_env->builtin_names[1] = "cd";
	m_env->builtin_names[2] = "pwd";
	m_env->builtin_names[3] = "export";
	m_env->builtin_names[4] = "unset";
	m_env->builtin_names[5] = "env";
	m_env->builtin_names[6] = "exit";
	m_env->builtin_functions[0] = ft_echo;
	m_env->builtin_functions[1] = ft_cd;
	m_env->builtin_functions[2] = ft_pwd;
	m_env->builtin_functions[3] = ft_export;
	m_env->builtin_functions[4] = ft_unset;
	m_env->builtin_functions[5] = ft_env;
	m_env->builtin_functions[6] = ft_exit;
}

int	check_builtin(char **builtin_names, char *name)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(builtin_names[i], name, ft_strlen(builtin_names[i]) + 1))
			return (i);
		i++;
	}
	return (i);
}

int	run_builtin(t_minishell_environment *min_environment, t_command_list *cmd, t_exec_env *in_exec)
{
	int		num;
	char	**data[2];

	num = check_builtin(min_environment->builtin_names, cmd->argv[0]);
	data[0] = cmd->argv;
	data[1] = min_environment->envp;
	in_exec->first_fd->r_code = min_environment->builtin_functions[num](data);
	return (0);
}
