/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:07:46 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/30 20:08:24 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	retrieve_filedescriptors(t_exec_env *in_exec, int num, int *save)
{
	t_fds	*tmp_fd;
	int		j;

	j = 1;
	tmp_fd = in_exec->first_fd;
	while (j < num)
	{
		tmp_fd = tmp_fd->next_fd;
		j++;
	}
	if (tmp_fd->infile != NO_FILE)
	{
		dup2(save[0], STDIN_FILENO);
		close(save[0]);
	}
	if (tmp_fd->outfile != NO_FILE)
	{
		dup2(save[1], STDOUT_FILENO);
		close(save[1]);
	}
}
