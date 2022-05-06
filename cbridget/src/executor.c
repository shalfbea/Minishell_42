/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/06 18:23:27 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell_environment *min_environment)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	in_exec.envp_in = min_environment->envp;
	if (ft_init(min_environment->first_group, &in_exec))
		return (1);
	if (run_commands(min_environment->first_group, &in_exec))
		return (1);
	else
		save_ex_code(min_environment, &in_exec);
//	ft_free(min_environment->first_group, &in_exec); it's commented out due to tests
	return (0);
}

void	save_ex_code(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	t_fds	*tmp_fd;

	tmp_fd = in_exec->first_fd;
	while (tmp_fd->next_fd)
		tmp_fd = tmp_fd->next_fd;
	min_environment->ex_code = tmp_fd->r_code;
}
