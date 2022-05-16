/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/16 22:03:41 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell_environment *min_environment)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	in_exec.num_com = min_environment->first_group->number_of_commands;
	if (ft_init(min_environment->first_group, &in_exec))
		return (1);
	if (run_commands(min_environment, min_environment->first_group, &in_exec))
		return (delete_heredoc(min_environment->first_group->first_command));
	else
		save_ex_code(min_environment, &in_exec);
	delete_heredoc(min_environment->first_group->first_command);
//	ft_free(min_environment->first_group, &in_exec);// it's commented out due to tests
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
