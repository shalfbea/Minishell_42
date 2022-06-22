/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/22 17:24:17 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_command_list *commands)
{
	t_exec_env	in_exec;
	int			err;

	in_exec.first_fd = NULL;
	if (ft_init(commands, &in_exec))
		return (1);
	err = run_commands(commands, &in_exec);
	if (err)
	{
		delete_heredoc(commands);
		ft_free(commands, &in_exec);
		return (err);
	}
	else
		save_ex_code(&in_exec);
	delete_heredoc(commands);
	ft_free(commands, &in_exec);
	return (0);
}

void	save_ex_code(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;

	tmp_fd = in_exec->first_fd;
	while (tmp_fd->next_fd)
		tmp_fd = tmp_fd->next_fd;
	g_ms_env.ex_code = tmp_fd->r_code;
}
