/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:05 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/10 14:17:13 by cbridget         ###   ########.fr       */
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
//	if (open_files(group->first_command, in_exec->first_fd))
//		return (ft_free(group, in_exec));
	return (0);
}

/*int	open_files(t_command_list *commands, t_fds *fds)
{
	checking_files();
	heredoc();
	while (commands)
	{
		if (commands->infile && !commands->redirect_flag_infile)
			fds->infile = open(commands->infile, O_RDONLY);
//		else if (commands->infile && commands->redirect_flag_infile)
//			fds->infile = heredoc();//do this
		if (commands->outfile && !commands->redirect_flag_outfile)
			fds->outfile = open(commands->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (commands->outfile && commands->redirect_flag_outfile)
			fds->outfile = open(commands->outfile,  O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fds->infile == -1 || fds->outfile == -1)
			return (1);

		commands = commands->next_command;
		fds = fds->next_fd;
	}
	return (0);
}*/

int	ft_free(t_logical_groups *group, t_exec_env *in_exec)
{
	free_min_env(group);
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
