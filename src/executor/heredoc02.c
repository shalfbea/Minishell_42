/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:41 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/31 18:57:58 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_heredoc(t_command_list *cmd)
{
	int		i;
	int		num;
	char	*name;

	num = 1;
	while (cmd)
	{
		i = 0;
		while ((cmd->redirects)[i])
		{
			if ((cmd->redirect_flags)[i] == REDIR_INSOURCE)
			{
				name = create_name(num);
				if (!name)
					return (1);
				unlink(name);
				free(name);
				break ;
			}
			i++;
		}
		num++;
		cmd = cmd->next_command;
	}
	return (1);
}

int	write_heredoc(int num, char *delim)
{
	int		fd;
	int		line;
	char	*str;
	char	*file_n;

	fd = create_file(num, &file_n);
	if (fd == -1)
		return (-1);
	line = 1;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			return (hd_close(str, file_n, fd));
		if (working_with_line(str, delim, line))
			break ;
		if ((size_t)write(fd, str, ft_strlen(str)) != ft_strlen(str))
			return (hd_close(str, file_n, fd));
		free(str);
		line++;
	}
	free(file_n);
	return (fd);
}

int	working_with_line(char *str, char *delim, int line)
{
	char	tmp;
	int		len;

	tmp = 0;
	len = ft_strlen(delim);
	if (str[0] == NO_FILE)
	{
		put_warning(line, delim);
		free(str);
		return (1);
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
		return (1);
	}
	if (tmp)
		str[ft_strlen(str)] = '\n';
	return (0);
}
