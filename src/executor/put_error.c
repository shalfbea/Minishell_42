/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:21:35 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/31 19:22:16 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_error(char *name, char flag)
{
	char	*str;
	int		length;

	if (flag == ERR_FEW_ARG)
		str = "too few arguments";
	else if (flag == ERR_MANY_ARG)
		str = "too many arguments";
	else if (flag == ERR_EXPORT || flag == ERR_UNSET)
		str = "not a valid identifier";
	else if (flag == ERR_EXIT)
		str = "numeric argument required";
	else if (flag)
		str = strerror(errno);
	else
		str = "command not found";
	length = ft_strlen(name);
	return (put_error_02(name, flag, str, length));
}

int	put_error_02(char *name, char flag, char *str, int length)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (flag == ERR_CD)
		write(STDERR_FILENO, "cd: ", 4);
	else if (flag == ERR_EXPORT)
		write(STDERR_FILENO, "export: `", 9);
	else if (flag == ERR_UNSET)
		write(STDERR_FILENO, "unset: `", 8);
	else if (flag == ERR_EXIT)
		write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, name, length);
	if (flag == ERR_EXPORT || flag == ERR_UNSET)
		write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, ": ", 2);
	length = ft_strlen(str);
	write(STDERR_FILENO, str, length);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
