/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:38:42 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/30 21:43:41 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_name(char *name, int length)
{
	char	**tmp_env;

	tmp_env = (char **)malloc(sizeof(char *) * (length + 2));
	if (!tmp_env)
	{
		free(name);
		return (1);
	}
	add_new_name_02(name, tmp_env, 0, 0);
	free(g_ms_env.envp);
	g_ms_env.envp = tmp_env;
	return (0);
}

void	add_new_name_02(char *name, char **tmp_env, int i, int j)
{
	char	flag;

	flag = 1;
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
}

void	add_var_evp(char *name, int flag)
{
	int		length;
	int		i;
	char	*tmp_name;

	length = 0;
	while (g_ms_env.envp[length])
		length++;
	tmp_name = add_var_evp_02(name, flag, length);
	if (!tmp_name)
		return ;
	i = find_name(name);
	if (i == length)
		add_new_name(tmp_name, length);
	else
		change_name(name, tmp_name, i);
}

char	*add_var_evp_02(char *name, int flag, int length)
{
	char	*tmp_name;
	int		i;

	if (flag == 10)
	{
		i = find_name(name);
		if (i == length)
			tmp_name = delete_pluse(name);
		else
		{
			add_value(name, i);
			return (NULL);
		}
	}
	else
	{
		i = find_name(name);
		tmp_name = ft_strdup(name);
	}
	return (tmp_name);
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
