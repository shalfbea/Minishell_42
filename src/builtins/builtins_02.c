/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:43:17 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/28 16:18:42 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	*path;
	int		lenght;

	path = getcwd(NULL, 0);
	if (!path)
		return (put_error(argv[0], 1));
	lenght = ft_strlen(path);
	if (write(STDOUT_FILENO, path, lenght) != lenght)
	{
		free(path);
		return (put_error(argv[0], 1));
	}
	free(path);
	if (write(STDOUT_FILENO, "\n", 1) != 1)
		return (put_error(argv[0], 1));
	return (0);
}

int	ft_env(char **argv)
{
	int		i;
	int		length;

	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
		return (put_error(argv[0], ERR_MANY_ARG));
	i = 0;
	while (g_ms_env.envp[i])
	{
		length = ft_strlen(g_ms_env.envp[i]);
		if (check_name(g_ms_env.envp[i], 1) == NO_VALUE)
		{
			i ++;
			continue ;
		}
		if (write(STDOUT_FILENO, g_ms_env.envp[i], length) != length)
			return (put_error(argv[0], 1));
		if (write(STDOUT_FILENO, "\n", 1) != 1)
			return (put_error(argv[0], 1));
		i++;
	}
	return (0);
}

int	echo_n(char flag)
{
	if (flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) != 1)
			return (1);
	}
	return (0);
}

int	arg_is_number(char *str)
{
	long	i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		j++;
	}
	i = new_atoi(str);
	if (j >= 17 && (!i || i == (long)-1))
		return (0);
	return (1);
}
