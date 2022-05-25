/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:44:04 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/25 16:52:21 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_command_list *commands, t_exec_env *in_exec)
{
	int	fd;
	int	j;
	int	num;
	t_command_list	*tmp_cmd;
	t_fds	*tmp_fd;

	num = 1;
	tmp_cmd = commands;
	tmp_fd = in_exec->first_fd;
	while (tmp_cmd)
	{
		j = 0;
		fd = -55;
		while ((tmp_cmd->redirects)[j])
		{
			if ((tmp_cmd->redirect_flags)[j] == REDIR_INSOURCE)
			{
				if (fd != -55)
					close(fd);
				fd = write_heredoc(num, (tmp_cmd->redirects)[j]);
				tmp_fd->hd_flag = j;
				if (fd == -1)
					return (1);
			}
			j++;
		}
		if (fd != -55)
			close(fd);
		tmp_cmd = tmp_cmd->next_command;
		tmp_fd = tmp_fd->next_fd;
		num++;
	}
	return (0);
}

int	write_heredoc(int num, char *delim)
{
	int	fd;
	int	len;
	int	line;
	char *str;
	char *file_n;
	char tmp;

	fd = create_file(num, &file_n);
	if (fd == -1)
		return (-1);
	len = ft_strlen(delim);
	line = 1;
	tmp = 0;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			return (hd_close(str, file_n, fd));
		if (str[0] == -55)
		{
			put_warning(line, delim);
			free(str);
			break ;
		}
		put_newline(str);
		if (str[ft_strlen(str) - 1] == '\n')
		{
			str[ft_strlen(str) - 1] = '\0';
			tmp = 1;
		}
		if (!ft_strncmp(str, delim, len + 1))
		{
			free(str);
			break ;
		}
		if (tmp)
		{
			str[ft_strlen(str)] = '\n';
			tmp = 0;
		}
		if ((size_t)write(fd, str, ft_strlen(str)) != ft_strlen(str))
			return (hd_close(str, file_n, fd));
		free(str);
		line++;
	}
	free(file_n);
	return (fd);
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

void	put_warning(int line, char *delim)
{
	char *str;

	str = ft_itoa(line);
	if (!str)
		return ;
	write(2, "\nminishell: warning: here-document at line ", 43);
	write(2, str, ft_strlen(str));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, delim, ft_strlen(delim));
	write(2, "')\n", 3);
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

int	create_file(int num, char **file_n)
{
	char	*name;
	int		fd;

	name = create_name(num);
	if (!name)
		return (-1);
	*file_n = name;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		free(name);
	return (fd);
}

char	*create_name(int num)
{
	char	*numbr;
	char	*name;

	numbr = ft_itoa(num);
	if (!numbr)
		return ((void *)0);
	name = ft_strjoin("/var/tmp/minishell", numbr);
	free(numbr);
	return (name);
}
