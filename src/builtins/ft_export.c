/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:46:13 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/28 18:21:48y cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_sort_env(char **argv)
{
	int		i;
	int		j;
	char	*name;

	i = 65;
	while (i < 123)
	{
		j = 0;
		while (g_ms_env.envp[j])
		{
			if (g_ms_env.envp[j][0] == i)
			{
				name = get_name(j);
				if (!name)
					return (1);
				if (g_ms_env.envp[j][find_value(j) - 1] != '=')
					printf("declare -x %s\n", name);
				else
				{
					if (printf("declare -x %s\"%s\"\n", name, &g_ms_env.envp[j][find_value(j)]) < 0)
					{
						free(name);
						return (put_error(argv[0], 1));
					}
				}
				free(name);
			}
			j++;
		}
		i++;
	}
	return (0);
}

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

int	find_value(int i)
{
	int	j;

	j = 0;
	while (g_ms_env.envp[i][j] != '=' && g_ms_env.envp[i][j])
		j++;
	if (g_ms_env.envp[i][j] == '=')
		return (++j);
	else
		return (j);
}

int	check_name(char *name, char flag)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	if (flag)
	{
		while (name[i] && name[i] != '=')
		{
			if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
				return (0);
			i++;
		}
		if (name[i] != '=')
			return (NO_VALUE);
	}
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

void	add_var_evp(char *name)
{
	int		length;
	int		i;
	char	*tmp_name;

	length = 0;
	i = find_name(name);
	tmp_name = ft_strdup(name);
	if (!tmp_name)
		return ;
	while (g_ms_env.envp[length])
		length++;
	if (i == length)
	{
		if (add_new_name(tmp_name, length))
			return ;
	}
	else
	{
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
}

int	add_new_name(char *name, int length)
{
	char	**tmp_env;
	char	flag;
	int		i;
	int		j;

	i = 0;
	j = 0;
	flag = 1;
	tmp_env = (char **)malloc(sizeof(char *) * (length + 2));
	if (!tmp_env)
	{
		free(name);
		return (1);
	}
	while (g_ms_env.envp[i])
	{
		if (name[0] <= g_ms_env.envp[i][0] && flag)
		{
			tmp_env[j] = name;
			flag = 0;
			j++;
		}
		else
		{
			tmp_env[j] = g_ms_env.envp[i];
			i++;
			j++;
		}
	}
	if (flag)
	{
		tmp_env[j] = name;
		j++;
	}
	tmp_env[j] = NULL;
	free(g_ms_env.envp);
	g_ms_env.envp = tmp_env;
	return (0);
}

int	find_name(char *name)
{
	int	i;
	int	j;

	i = 0;
	while (g_ms_env.envp[i])
	{
		j = 0;
		while (name[j] && name[j] != '=' && name[j] == g_ms_env.envp[i][j])
			j++;
		if ((!name[j] || name[j] == '=') && (g_ms_env.envp[i][j] == '=' || !g_ms_env.envp[i][j]))
			return (i);
		i++;
	}
	return (i);
}
