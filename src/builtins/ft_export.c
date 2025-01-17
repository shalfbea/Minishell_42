/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:46:13 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/03 17:18:38 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_sort_env(void)
{
	int		i;
	int		j;
	int		err;

	i = 65;
	err = 0;
	while (i < 123)
	{
		j = 0;
		while (g_ms_env.envp[j])
		{
			if (g_ms_env.envp[j][0] == i)
				err = print_sort_env_02(j);
			if (err)
				return (err);
			j++;
		}
		i++;
	}
	return (0);
}

int	print_sort_env_02(int j)
{
	char	*name;

	name = get_name(j);
	if (!name)
		return (1);
	if (g_ms_env.envp[j][find_value(j) - 1] != '=')
		printf("declare -x %s\n", name);
	else
		printf("declare -x %s\"%s\"\n", name, \
		&g_ms_env.envp[j][find_value(j)]);
	free(name);
	return (0);
}

void	add_value(char *name, int i)
{
	int		len;
	int		j;
	char	*res;

	j = 0;
	len = 0;
	len = ft_strlen(g_ms_env.envp[i]);
	while (g_ms_env.envp[i][j] != '=' && g_ms_env.envp[i][j])
		j++;
	if (g_ms_env.envp[i][j] != '=')
		len++;
	j = 0;
	while (name[j] != '=' && name[j])
		j++;
	j++;
	if (!name[j])
		return ;
	while (name[j++])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return ;
	add_value_02(name, i, res);
}

void	add_value_02(char *name, int i, char *res)
{
	int	j;
	int	len;

	j = -1;
	len = 0;
	while (g_ms_env.envp[i][++j])
		res[j] = g_ms_env.envp[i][j];
	while (g_ms_env.envp[i][len] != '=' && g_ms_env.envp[i][len])
		len++;
	if (g_ms_env.envp[i][len] != '=')
		res[j++] = '=';
	len = 0;
	while (name[len] != '=')
		len++;
	len++;
	while (name[len])
	{
		res[j] = name[len];
		len++;
		j++;
	}
	res[j] = '\0';
	free(g_ms_env.envp[i]);
	g_ms_env.envp[i] = res;
}

char	*delete_pluse(char *name)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(name);
	res = (char *)malloc(sizeof(char) * i);
	if (!res)
		return (res);
	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] == '+')
			i++;
		else
		{
			res[j] = name[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}
