/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:26:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/11 14:47:25 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	working_with_redirects(t_logical_groups *group, t_command_list *cmd, t_exec_env *in_exec, int num)
{
	t_fds	*tmp_fd;
	int		j;

	group = NULL;
	j = 1;
	tmp_fd = in_exec->first_fd;
	while (j < num)
	{
		tmp_fd = tmp_fd->next_fd;
		j++;
	}
	if (check_files(cmd, tmp_fd, num))
		return (1);
//	else if (check_cmd())
//		return (1);
	//enter run flags!
	return (0);
}

int	check_files(t_command_list *cmd, t_fds *tmp_fd, int num)
{
	int	j;
	char *name;

	j = 0;
	while (cmd->redirects[j])
	{
		if (cmd->redirect_flags[j] == 0 || cmd->redirect_flags[j] == 1)
		{
			if (tmp_fd->outfile != -55)
				close(tmp_fd->outfile);
			if (cmd->redirect_flags[j] == 0)
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (tmp_fd->outfile == -1)
				return (put_error(cmd->redirects[j]));
		}
		else if (cmd->redirect_flags[j] == 2 || cmd->redirect_flags[j] == 3)
		{
			if (tmp_fd->infile != -55)
				close(tmp_fd->infile);
			if (tmp_fd->hd_flag != j && cmd->redirect_flags[j] == 2)
				tmp_fd->infile = open(cmd->redirects[j], O_RDONLY);
			else if (tmp_fd->hd_flag == j && cmd->redirect_flags[j] == 3)
			{
				name = create_name(num);
				if (!name)
					return (1);
				tmp_fd->infile = open(name, O_RDONLY);
				free(name);
			}
			else
				tmp_fd->infile = -55;
			if (tmp_fd->infile == -1)
				return (put_error(cmd->redirects[j]));
		}
		j++;
	}
	return (0);
}

int	put_error(char *name)
{
	char	*str;
	int		length;

	str = strerror(errno);
	length = ft_strlen(name);
	write(2, "minishell: ", 11);
	write(2, name, length);
	write(2, ": ", 2);
	length = ft_strlen(str);
	write(2, str, length);
	write(2, "\n", 1);
	return (1);
}
