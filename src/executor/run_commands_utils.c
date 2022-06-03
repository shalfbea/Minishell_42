/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:34:00 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/03 15:41:43 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_pids(void)
{
	g_ms_env.pids = (pid_t *)malloc(sizeof(pid_t) \
	* g_ms_env.number_of_commands);
	if (!g_ms_env.pids)
		return (1);
	return (0);
}

int	ft_wait(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;
	int		i;

	i = 0;
	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		waitpid(g_ms_env.pids[i], &(tmp_fd->r_code), 0);
		if (WIFEXITED(tmp_fd->r_code))
			tmp_fd->r_code = WEXITSTATUS(tmp_fd->r_code);
		else if (WIFSIGNALED(tmp_fd->r_code))
			tmp_fd->r_code = ERR_SIG + WTERMSIG(tmp_fd->r_code);
		else
			tmp_fd->r_code = 1;
		if (tmp_fd->r_code == EXEC_ERROR)
			return (ft_kill(in_exec));
		tmp_fd = tmp_fd->next_fd;
		i++;
	}
	return (0);
}

int	ft_kill(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;
	int		i;

	i = 0;
	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		kill(g_ms_env.pids[i], 2);
		tmp_fd = tmp_fd->next_fd;
		i++;
	}
	return (1);
}
