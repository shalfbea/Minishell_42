/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:45:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/24 18:15:15 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_evp(char *variable)
{
	int		i;
	int		j;
	int		length;
	char	**tmp_env;
	
	i = 0;
	while (g_ms_env.envp[i])
		i++;
	tmp_env = (char **)malloc(sizeof(char *) * i);
	if (!tmp_env)
		return ;
	i = 0;
	j = 0;
	length = ft_strlen(variable);
	while (g_ms_env.envp[i])
	{
		if (ft_strncmp(g_ms_env.envp[i], variable, length))
		{
			tmp_env[j] = g_ms_env.envp[i];
			i++;
			j++;
		}
		else
		{
			free(g_ms_env.envp[i]);
			i++;
		}
	}
	tmp_env[j] = NULL;
	free(g_ms_env.envp);
	g_ms_env.envp = tmp_env;
}
