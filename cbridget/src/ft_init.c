/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/13 12:37:41 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_logical_groups *group, t_exec_env *in_exec)
{
	if (group->number_of_commands > 1)
	{
		if (open_pipes(group, in_exec))
			return (1);
	}
	if (alloc_lsts(in_exec, group->number_of_commands))
		return (ft_free(group, in_exec));
	if (heredoc(group, in_exec))
		return (ft_free(group, in_exec));
	return (0);
}

int	ft_free(t_logical_groups *group, t_exec_env *in_exec)
{
	group = NULL;//fix it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	free_min_env(group);
	free_lsts(in_exec->first_fd);
	free((in_exec->_pipes)[0]);
	free(in_exec->_pipes);
	return (1);
}

void	free_min_env(t_logical_groups *group)
{
	t_command_list	*commands;
	t_command_list	*tmp_com;
	int	i;

	commands = group->first_command;
	while (commands)
	{
		i = 0;
		tmp_com = commands;
		commands = commands->next_command;
		while ((tmp_com->argv)[i])
		{
			free((tmp_com->argv)[i]);
			i++;
		}
//		if (tmp_com->infile)   fix it
//			free(tmp_com->infile);
//		if (tmp_com->outfile)
//			free(tmp_com->outfile);
		free(tmp_com->argv);
		free(tmp_com);
	}
	group->first_command = NULL;
}
