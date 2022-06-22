/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:28:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/22 17:14:44 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_command_list *tmp_cmd, t_exec_env *in_exec, int i)
{
	int	p_flag;

	if (tmp_cmd->next_command)
		p_flag = 1;
	else
		p_flag = 0;
	if ((i + 1) % 2 && p_flag)
	{
		if (pipe((in_exec->new_pipes)[0]) == -1)
		{
			if (i)
				close((in_exec->new_pipes)[1][0]);
			return (-1);
		}
	}
	else if (p_flag)
	{
		if (pipe((in_exec->new_pipes)[1]) == -1)
		{
			close((in_exec->new_pipes)[0][0]);
			return (-1);
		}
	}
	return (p_flag);
}

void	close_pipes(t_exec_env *in_exec, int cmd_num, int p_flag)
{
	if (cmd_num % 2)
	{
		if (cmd_num != 1)
			close((in_exec->new_pipes)[1][0]);
		if (p_flag)
			close((in_exec->new_pipes)[0][1]);
	}
	else
	{
		close((in_exec->new_pipes)[0][0]);
		if (p_flag)
			close((in_exec->new_pipes)[1][1]);
	}
}
