/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:40:35 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/30 21:40:37 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_evp(char *variable)
{
	int		i;
	char	**tmp_env;

	i = 0;
	while (g_ms_env.envp[i])
		i++;
	if (i == find_name(variable))
		return ;
	tmp_env = (char **)malloc(sizeof(char *) * i);
	if (!tmp_env)
		return ;
	i = del_var_evp_02(tmp_env, variable);
	tmp_env[i] = NULL;
	free(g_ms_env.envp);
	g_ms_env.envp = tmp_env;
}

int	del_var_evp_02(char **tmp_env, char *variable)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	length = ft_strlen(variable);
	while (g_ms_env.envp[i])
	{
		if (!ft_strncmp(g_ms_env.envp[i], variable, length) && \
			g_ms_env.envp[i][length] == '=')
		{
			free(g_ms_env.envp[i]);
			i++;
		}
		else
		{
			tmp_env[j] = g_ms_env.envp[i];
			i++;
			j++;
		}
	}
	return (j);
}
