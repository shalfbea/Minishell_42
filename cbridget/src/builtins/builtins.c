/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/21 17:59:35 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	char	flag;
	int		length;
	int		i;

	i = 1;
	flag = 1;
	if (argv[i] && !ft_strncmp(argv[i], "-n", 3))
	{
		flag = 0;
		i++;
	}
	while (argv[i])
	{
		length = ft_strlen(argv[i]);
		if (write(STDOUT_FILENO, argv[i], length) != length)
			return (1);
		i++;
		if (argv[i] && write(STDOUT_FILENO, " ", 1) != 1)
			return (1);
	}
	if (flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) != 1)
			return (1);
	}
	return (0);
}

int	ft_cd(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
		i++;
	if (i == 1)
		return (put_error(argv[0], 3));
	else if (i != 2)
		return (put_error(argv[0], 5));
	if (chdir(argv[1]))
		return (put_error(argv[1], 7));
	return (0);
}

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

int	ft_export(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		return (print_sort_env(argv));
	while (argv[i])
	{
		if (check_name(argv[i]))
			add_var_evp(argv[i]);
		else
			put_error(argv[i], 13);
		i++;
	}
	return (0);
}

int	ft_unset(char **argv)
{
	argv = NULL;
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
		return (put_error(argv[0], 5));
	i = 0;
	while (g_ms_env.envp[i])
	{
		length = ft_strlen(g_ms_env.envp[i]);
		if (write(STDOUT_FILENO, g_ms_env.envp[i], length) != length)
			return (put_error(argv[0], 1));
		if (write(STDOUT_FILENO, "\n", 1) != 1)
			return (put_error(argv[0], 1));
		i++;
	}
	return (0);
}

int	ft_exit(char **argv)
{
	argv = NULL;
	return (0);
}
