/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:28:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/20 14:20:06 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_command_list *commands, t_exec_env *in_exec)
{
	int	i;

	i = 0;
	if (alloc_pipes(&(in_exec->_pipes), g_ms_env.number_of_commands - 1))
		return (ft_free(commands, in_exec));
	while (i < g_ms_env.number_of_commands - 1)
	{
		if (pipe((in_exec->_pipes)[i]) < 0)
			return (ft_free(commands, in_exec));
		i++;
	}
	return (0);
}

int	alloc_pipes(int ***pipes, int num)
{
	int i;

	i = 1;
	*pipes = malloc(sizeof(int *) * (num + 1));
	if (!*pipes)
		return (1);
	(*pipes)[0] = malloc(sizeof(int) * num * 2);
	if (!(*pipes)[0])
	{
		free(*pipes);
		*pipes = NULL;
		return (1);
	}
	while (i < num)
	{
		(*pipes)[i] = (*pipes)[0] + i * 2;
		i++;
	}
	(*pipes)[i] = (void *)0;
	return (0);
}

void	close_pipes(t_exec_env *in_exec, int num)
{
	int	i;

	i = 0;
	num -= 1;
	while (i < num)
	{
		close((in_exec->_pipes)[i][0]);
		close((in_exec->_pipes)[i][1]);
		i++;
	}
}
