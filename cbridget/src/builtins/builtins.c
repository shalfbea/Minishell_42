/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:19:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/15 18:12:02 by cbridget         ###   ########.fr       */
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
	if (!ft_strncmp(argv[i], "-n", 4))
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
	data = NULL;
	return (0);
}

int	ft_pwd(char ***data)
{
	data = NULL;
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
	data = NULL;
	return (0);
}

int	ft_exit(char ***data)
{
	data = NULL;
	return (0);
}
