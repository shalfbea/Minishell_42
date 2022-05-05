/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:28:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/05 14:05:18 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	int	i;

	i = 0;
	if (alloc_pipes(&(in_exec->_pipes), min_environment->number_of_commands - 1))
	{
		free_min_env(min_environment);
		free_lsts(in_exec->first_fd);
		return (1);
	}
	while (i < min_environment->number_of_commands - 1)
	{
		if (pipe((in_exec->_pipes)[i]) < 0)
			return (ft_free(min_environment, in_exec));
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
