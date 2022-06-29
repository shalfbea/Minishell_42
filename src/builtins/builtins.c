/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/29 16:55:28 by cbridget         ###   ########.fr       */
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
	if (argv[i])
		skipp_n(argv[i]);
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
	{
		flag = 0;
		i++;
		if (argv[i])
			skipp_n(argv[i]);
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
	return (echo_n(flag));
}

int	ft_cd(char **argv)
{
	char	*path;
	char	*str;

	if (!argv[1])
		return (put_error(argv[0], ERR_FEW_ARG));
	else if (argv[2])
		return (put_error(argv[0], ERR_MANY_ARG));
	if (chdir(argv[1]))
		return (put_error(argv[1], ERR_CD));
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n");
		return (0);
	}
	str = ft_strjoin("PWD=", path);
	free(path);
	if (!str)
		return (1);
	add_var_evp(str, 0);
	free(str);
	return (0);
}

int	ft_export(char **argv)
{
	int	i;
	int	err;
	int	flag;

	i = 1;
	err = 0;
	if (!argv[i])
		return (print_sort_env());
	while (argv[i])
	{
		flag = check_name(argv[i], 3);
		if (flag)
			add_var_evp(argv[i], flag);
		else
		{
			put_error(argv[i], ERR_EXPORT);
			err = 1;
		}
		i++;
	}
	return (err);
}

int	ft_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_name(argv[i], 0))
			del_var_evp(argv[i]);
		else
		{
			put_error(argv[i], ERR_UNSET);
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **argv)
{
	long	err;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!argv[1])
		return (SHELL_CLOSE);
	if (arg_is_number(argv[1]))
	{
		if (argv[2])
		{
			put_error(argv[0], ERR_MANY_ARG);
			g_ms_env.ex_code = 1;
			return (1);
		}
		err = new_atoi(argv[1]);
		g_ms_env.ex_code = err % 256;
		return (SHELL_CLOSE);
	}
	put_error(argv[1], ERR_EXIT);
	g_ms_env.ex_code = 255;
	return (SHELL_CLOSE);
}
