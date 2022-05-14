/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/13 18:10:10 by cbridget         ###   ########.fr       */
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
	free_group(group->first_command);
	group->first_command = NULL;
	free_lsts(in_exec->first_fd);
	free((in_exec->_pipes)[0]);
	free(in_exec->_pipes);
	return (1);
}

void	free_group(t_command_list *cmd)
{
	t_command_list	*tmp_cmd;
	int	i;

	while (cmd)
	{
		i = 0;
		tmp_cmd = cmd;
		cmd = cmd->next_command;
		free_vector(tmp_cmd->argv);
		free_vector(tmp_cmd->redirects);
		free(tmp_cmd->redirect_flags);
		free(tmp_cmd->argv);
		free(tmp_cmd);
	}
}

void	free_vector(char **vct)
{
	int	i;

	i = 0;
	if (!vct)
		return ;
	while (vct[i])
	{
		free(vct[i]);
		i++;
	}
	free(vct);
}
