/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/30 19:13:17 by cbridget         ###   ########.fr       */
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
	char	*path;
	char	*str;

	i = 1;
	while (argv[i])
		i++;
	if (i == 1)
		return (put_error(argv[0], ERR_FEW_ARG));
	else if (i != 2)
		return (put_error(argv[0], ERR_MANY_ARG));
	if (chdir(argv[1]))
		return (put_error(argv[1], ERR_CD));
	path = getcwd(NULL, 0);
	if (!path)
		return (put_error(argv[0], 1));
	str = ft_strjoin("PWD=", path);
	free(path);
	if (!str)
		return (1);
	add_var_evp(str, 0);
	free(str);
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
	int	err;

	i = 1;
	err = 0;
	while (argv[i])
	{
		if (check_name(argv[i], 0))
			del_var_evp(argv[i]);
		else
		{
			put_error(argv[i], ERR_UNSET);
			err = 1;
		}
		i++;
	}
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

int	ft_exit(char **argv)
{
	int	err;

	if (!argv[1])
	{
		g_ms_env.ex_code = 0;
		return (SHELL_CLOSE);
	}
	if (arg_is_number(argv[1]))
	{
		if (argv[2])
		{
			put_error(argv[0], ERR_MANY_ARG);
			g_ms_env.ex_code = 1;
			return (1);
		}
		err = ft_atoi(argv[1]);
		g_ms_env.ex_code = err % 256;
		return (SHELL_CLOSE);
	}
	put_error(argv[1], ERR_EXIT);
	g_ms_env.ex_code = 255;
	return (SHELL_CLOSE);
}

int	arg_is_number(char *str)
{
	int	i;

	i = 0;
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
	}
	return (1);
}
