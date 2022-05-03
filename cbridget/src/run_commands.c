/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:44:56 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:44 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_commands(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	int	i;
//	t_command_list	*tmp_min;
	t_fds	*tmp_in;
//	if (min_environment->number_of_commands == 1 && min_environment->first_command->build_in_flag)
//		run_build_in();// it needs to be done
	i = 0;
//	tmp_min = min_environment->first_command;
	tmp_in = in_exec->first_fd;
	while (i < min_environment->number_of_commands)
	{
		tmp_in->pid_com = fork();
		if (tmp_in->pid_com < 0)
			return (ft_free(min_environment, in_exec, 1));
		if (tmp_in->pid_com == 0)
			ft_exec(min_environment, in_exec, i + 1);
		tmp_in = tmp_in->next_fd;
		i++;
	}
	return (0);
}

void	ft_exec(t_minishell_environment *min_environment, t_exec_env *in_exec,/*t_fds *fd,*/ int i)
{
	ft_close_fd(in_exec->_pipes, i, min_environment->number_of_commands);
}

void	ft_close_fd(int	*_pipes, int i, int length)
{
	int	j;

	j = 0;
	while (j < (length - 1) * 2)
	{
		if (i == 1 && j == 0)
			close(_pipes[j + 1]);
		else if (i == length - 1 && j + 2 == (length - 1) * 2)
			close(_pipes[j]);
		else if (i > 1 && i < length - 1 && j == i - 2)//it needs to be done!!!
			close(_pipes[j]);
		else if (i > 1 && i < length - 1 && j == i + 2)
			close(_pipes[j + 1]);
		else
		{
			close(_pipes[j]);
			close(_pipes[j + 1]);
		}
		j += 2;
	}
}
