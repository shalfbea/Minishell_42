/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/05 14:07:32 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	if (min_environment->number_of_commands > 1)
	{
		if (open_pipes(min_environment, in_exec))
			return (1);
	}
	if (alloc_lsts(in_exec, min_environment->number_of_commands))
		return (ft_free(min_environment, in_exec));
	if (open_files(min_environment->first_command, in_exec->first_fd))
		return (ft_free(min_environment, in_exec));
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
		fds = fds->next_fd;
	}
	return (0);
}

int	ft_free(t_minishell_environment *min_environment, t_exec_env *in_exec)
{
	free_min_env(min_environment);
	free_lsts(in_exec->first_fd);
	free((in_exec->_pipes)[0]);
	free(in_exec->_pipes);
	return (1);
}

void	free_min_env(t_minishell_environment *min_environment)
{
	t_command_list	*commands;
	t_command_list	*tmp_com;
	int	i;

	commands = min_environment->first_command;
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
		free(tmp_com->argv);
		free(tmp_com);
	}
	min_environment->first_command = NULL;
}
