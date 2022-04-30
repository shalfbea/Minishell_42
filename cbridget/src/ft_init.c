/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/04/30 19:12:19 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	if (min_environment->number_of_commands > 1)
	{
		in_exec->_pipes = malloc(sizeof(int) * (min_environment->number_of_commands - 1) * 2);
		if (!in_exec->_pipes)
			return (1);
		if (open_pipes(in_exec->_pipes, (min_environment->number_of_commands - 1) * 2))
			return (1);
	}
	if (alloc_lsts(in_exec, min_environment->number_of_commands))
		return (1);
	if (open_files(min_environment->first_command, in_exec->first_fd))
		return (1);
	return (0);
}

int	open_pipes(int *_pipes, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pipe(&_pipes[i]) < 0)
		{
			free(_pipes);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	open_files(t_command_list *commands, t_fds *fds)
{
	while (commands)
	{
		if (commands->infile && !commands->redirect_flag_infile)
			fds->infile = open(commands->infile, O_RDONLY);
//		else if (commands->infile && commands->redirect_flag_infile)
//			fds->infile = here_doc();//do this
		if (commands->outfile && !commands->redirect_flag_outfile)
			fds->outfile = open(commands->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (commands->outfile && commands->redirect_flag_outfile)
			fds->outfile = open(commands->outfile,  O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fds->infile == -1 || fds->outfile == -1)
			return (1);

		commands = commands->next_command;
	}
	return (0);
}

int	ft_free(t_exec_env *in_exec)
{
	if (in_exec->first_fd)
		free_lsts(in_exec->first_fd);
	free(in_exec->_pipes);
	return (1);
}
