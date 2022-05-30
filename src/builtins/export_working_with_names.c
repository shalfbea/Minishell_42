/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_working_with_names.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:35:10 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/30 21:35:12 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(int i)
{
	char	*res;
	int		len;
	int		j;

	j = 0;
	len = find_value(i);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (res);
	while (j < len)
	{
		res[j] = g_ms_env.envp[i][j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	check_name(char *name, char flag)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	if (flag)
		return (check_name_02(name, flag, i));
	else
	{
		while (name[i])
		{
			if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_name_02(char *name, char flag, int i)
{
	while (name[i] && name[i] != '=' && name[i] != '+')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	if (flag == 3 && name[i] == '+')
	{
		i++;
		if (name[i] != '=')
			return (0);
		return (10);
	}
	if (name[i] != '=')
		return (NO_VALUE);
	return (1);
}

void	change_name(char *name, char *tmp_name, int i)
{
	int	length;

	length = 0;
	while (name[length] != '=' && name[length])
		length++;
	if (!name[length])
		free(tmp_name);
	else
	{
		free(g_ms_env.envp[i]);
		g_ms_env.envp[i] = tmp_name;
	}
}

int	find_name(char *name)
{
	int	i;
	int	j;

	i = 0;
	while (g_ms_env.envp[i])
	{
		j = 0;
		while (name[j] && name[j] != '=' && name[j] != '+' && \
				name[j] == g_ms_env.envp[i][j])
			j++;
		if ((!name[j] || name[j] == '=' || name[j] == '+') && \
			(g_ms_env.envp[i][j] == '=' || !g_ms_env.envp[i][j]))
			return (i);
		i++;
	}
	return (i);
}
