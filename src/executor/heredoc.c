/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:44:04 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/31 18:55:19 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_command_list *commands, t_exec_env *in_exec)
{
	int				num;
	t_command_list	*tmp_cmd;
	t_fds			*tmp_fd;

	num = 1;
	tmp_cmd = commands;
	tmp_fd = in_exec->first_fd;
	g_ms_env.pids = (pid_t *)malloc(sizeof(pid_t) * 1);
	if (!g_ms_env.pids)
		return (1);
	while (tmp_cmd)
	{
		if (heredoc_check_pipeline(tmp_cmd, tmp_fd, num))
			return (1);
		tmp_cmd = tmp_cmd->next_command;
		tmp_fd = tmp_fd->next_fd;
		num++;
	}
	free(g_ms_env.pids);
	g_ms_env.pids = NULL;
	return (0);
}

int	heredoc_check_pipeline(t_command_list *tmp_cmd, t_fds *tmp_fd, int num)
{
	int	j;
	int	err;

	j = 0;
	while ((tmp_cmd->redirects)[j])
	{
		if ((tmp_cmd->redirect_flags)[j] == REDIR_INSOURCE)
		{
			if (fr_heredoc(tmp_cmd, num, j))
				return (1);
			waitpid(g_ms_env.pids[0], &err, 0);
			if (WIFEXITED(err))
				err = WEXITSTATUS(err);
			else
			{
				g_ms_env.ex_code = 1;
				return (1);
			}
			tmp_fd->hd_flag = j;
			if (err)
				return (1);
		}
		j++;
	}
	return (0);
}

int	fr_heredoc(t_command_list *tmp_cmd, int num, int j)
{
	int	err;

	g_ms_env.pids[0] = fork();
	if (g_ms_env.pids[0] < 0)
		return (1);
	if (g_ms_env.pids[0] == 0)
	{
		err = write_heredoc(num, (tmp_cmd->redirects)[j]);
		if (err == -1)
			exit(1);
		else
			exit(0);
	}
	return (0);
}

void	put_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (str[len - 1] != '\n')
		write(STDOUT_FILENO, "\n", 1);
}

int	hd_close(char *str, char *file_n, int fd)
{
	if (str)
		free(str);
	close(fd);
	unlink(file_n);
	free(file_n);
	return (-1);
}
