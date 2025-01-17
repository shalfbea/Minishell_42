/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/28 18:42:28 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_command_list *commands, t_exec_env *in_exec)
{
	if (alloc_lsts(in_exec, g_ms_env.number_of_commands))
		return (ft_free(commands, in_exec));
	if (heredoc(commands, in_exec))
	{
		delete_heredoc(commands);
		return (ft_free(commands, in_exec));
	}
	return (0);
}

int	ft_free(t_command_list *commands, t_exec_env *in_exec)
{
	free_commands(commands);
	if (in_exec)
		free_lsts(in_exec->first_fd);
	if (g_ms_env.pids)
	{
		free(g_ms_env.pids);
		g_ms_env.pids = NULL;
	}
	g_ms_env.number_of_commands = 0;
	return (1);
}

void	free_commands(t_command_list *cmd)
{
	t_command_list	*tmp_cmd;

	while (cmd)
	{
		tmp_cmd = cmd;
		cmd = cmd->next_command;
		free_vector(tmp_cmd->argv);
		free_vector(tmp_cmd->redirects);
		if (tmp_cmd->redirect_flags)
			free(tmp_cmd->redirect_flags);
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
