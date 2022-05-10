/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:26:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/10 15:47:22 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	working_with_redirects(t_logical_groups *group, t_command_list *cmd, t_exec_env *in_exec, int num)
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
	j = 0;
	int fd = -55;
	heredoc();
	while (cmd->redirects[j])
	{
		if (cmd->redirect_flags[j] == 0 || cmd->redirect_flags[j] == 1)
		{
			if (tmp_fd->outfile != -55)
			{
				close(tmp_fd->outfile);
				tmp_fd->outfile = -55;
			}
			if (cmd->redirect_flags[j] == 0)
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (tmp_fd->outfile == -1)
			{
				tmp_fd->r_code = 1;
				return (put_error());
			}
		}
		else if (cmd->redirect_flags[j] == 2)
		{
			if (tmp_fd->infile != -55 && tmp_fd->re_flag < j)
			{
				close(tmp_fd->infile);
/*				if (tmp_fd->re_flag)
				{
					unlink();
					tmp_fd->re_flag = -1;
				}*/
				tmp_fd->infile = -55;
			}
			else if (fd != -55)
			{
				close(fd);
				fd = -55;
			}
			if (tmp_fd->re_flag < j)
				tmp_fd->infile = open(cmd->redirects[j], O_RDONLY);
			else
				fd = open(cmd->redirects[j], O_RDONLY);
			if (fd == -1 || tmp_fd->infile == -1)
			{
				tmp_fd->r_code = 1;
				return (put_error());
			}
		}
	}
	if (fd != -55)
		close(fd);
	return (0);
}

int	put_error()
{
	return (1);
}
