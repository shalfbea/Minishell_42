/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:52:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/31 18:54:14 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file(int num, char **file_n)
{
	char	*name;
	int		fd;

	name = create_name(num);
	if (!name)
		return (-1);
	*file_n = name;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
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

void	put_warning(int line, char *delim)
{
	char	*str;

	str = ft_itoa(line);
	if (!str)
		return ;
	write(2, "\nminishell: warning: here-document at line ", 43);
	write(2, str, ft_strlen(str));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, delim, ft_strlen(delim));
	write(2, "')\n", 3);
}
