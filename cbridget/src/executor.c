/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/21 18:01:39 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_command_list *commands)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	in_exec._pipes = NULL;
	if (ft_init(commands, &in_exec))
		return (1);
	if (run_commands(commands, &in_exec))
	{
//		ft_free(commands, &in_exec);
		return (delete_heredoc(commands));
	}
	else
		save_ex_code(&in_exec);
	delete_heredoc(commands);
//	ft_free(commands, &in_exec);// it's commented out due to tests
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
