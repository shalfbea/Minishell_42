/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/17 21:21:27 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char ***data)
{
	char	**argv;
	char	flag;
	int		length;
	int		i;

	argv = data[0];
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

int	ft_cd(char ***data)
{
	char	**argv;
	int		i;

	i = 1;
	argv = data[0];
	while (argv[i])
		i++;
	if (i == 1)
		return (put_error("cd", 3));
	else if (i != 2)
		return (put_error("cd", 5));
	if (chdir(argv[1]))
		return (put_error(argv[1], 7));
	return (0);
}

int	ft_pwd(char ***data)
{
	char	**argv;
	char	*path;
	int		lenght;

	argv = data[0];
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

int	ft_export(char ***data)
{
	data = NULL;
	return (0);
}

int	ft_unset(char ***data)
{
	data = NULL;
	return (0);
}

int	ft_env(char ***data)
{
	char	**env;
	int		i;
	int		length;

	i = 0;
	env = data[1];
	while (env[i])
	{
		length = ft_strlen(env[i]);
		if (write(STDOUT_FILENO, env[i], length) != length)
			return (put_error);//do this!!!!
	}
	return (0);
}

int	ft_exit(char ***data)
{
	data = NULL;
	return (0);
}
