/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:47:39 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/03 13:36:27 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_lsts(t_exec_env *in_exec, int num)
{
	int		i;
	t_fds	**tmp_fd;

	i = 0;
	tmp_fd = &in_exec->first_fd;
	while (i < num)
	{
		if (i == 0)
		{
			if (create_lst(tmp_fd))
				return (1);
		}
		else
		{
			if (create_lst(&(*tmp_fd)->next_fd))
				return (1);
			tmp_fd = &(*tmp_fd)->next_fd;
		}
		i++;
	}
	return (0);
}

int	create_lst(t_fds **lst)
{
	*lst = malloc(sizeof(t_fds) * 1);
	if (!(*lst))
		return (1);
	(*lst)->infile = -55;
	(*lst)->outfile = -55;
	(*lst)->next_fd = NULL;
	return (0);
}

void	free_lsts(t_fds *lst)
{
	t_fds	*tmp_lst;

	while (lst)
	{
		tmp_lst = lst;
		lst = lst->next_fd;
		free(tmp_lst);
	}
}
