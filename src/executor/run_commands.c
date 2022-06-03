/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:44:56 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/03 15:42:10 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_commands(t_command_list *commands, t_exec_env *in_exec)
{
	if (g_ms_env.number_of_commands == 1 && \
		check_builtin(commands->argv[0]) < NUM_BULTINS)
		return (run_builtin(commands, in_exec, 1));
	if (alloc_pids())
		return (ft_free(commands, in_exec));
	if (create_process(commands, in_exec))
		return (1);
	close_pipes(in_exec, g_ms_env.number_of_commands);
	if (ft_wait(in_exec))
		return (1);
	return (0);
}

int	create_process(t_command_list *commands, t_exec_env *in_exec)
{
	int				i;
	t_command_list	*tmp_cmd;
	t_fds			*tmp_in;

	i = 0;
	tmp_cmd = commands;
	tmp_in = in_exec->first_fd;
	while (i < g_ms_env.number_of_commands)
	{
		g_ms_env.pids[i] = fork();
		if (g_ms_env.pids[i] < 0)
			return (ft_free(commands, in_exec));
		if (g_ms_env.pids[i] == 0)
			ft_exec(tmp_cmd, in_exec, i + 1);
		tmp_cmd = tmp_cmd->next_command;
		tmp_in = tmp_in->next_fd;
		i++;
	}
	return (0);
}

void	ft_exec(t_command_list *cmd, t_exec_env *in_exec, int i)
{
	int	j;

	j = 1;
	create_pipeline(in_exec->_pipes, i, g_ms_env.number_of_commands);
	if (check_builtin(cmd->argv[0]) < NUM_BULTINS)
		exit(run_builtin(cmd, in_exec, i));
	if (working_with_redirects(cmd, in_exec, i))
		exit(1);
	swap_filedescriptors(in_exec, i, NULL);
	if (check_cmd(&cmd->argv[0]))
		exit(ERR_NOCMD);
	execve((cmd->argv)[0], cmd->argv, g_ms_env.envp);
	exit(EXEC_ERROR);
}

void	swap_filedescriptors(t_exec_env *in_exec, int com, int *save)
{
	t_fds	*tmp_fd;
	int		j;

	j = 1;
	tmp_fd = in_exec->first_fd;
	while (j < com)
	{
		tmp_fd = tmp_fd->next_fd;
		j++;
	}
	if (tmp_fd->infile != NO_FILE)
	{
		if (save)
			save[0] = dup(STDIN_FILENO);
		dup2(tmp_fd->infile, STDIN_FILENO);
		close(tmp_fd->infile);
	}
	if (tmp_fd->outfile != NO_FILE)
	{
		if (save)
			save[1] = dup(STDOUT_FILENO);
		dup2(tmp_fd->outfile, STDOUT_FILENO);
		close(tmp_fd->outfile);
	}
}

void	create_pipeline(int	**pipes, int com, int length)
{
	int	j;

	j = 0;
	while (j < length - 1)
	{
		if ((com == 1 && j == 0) || (com > 1 && com < length && com - 1 == j))
		{
			close(pipes[j][0]);
			dup2(pipes[j][1], STDOUT_FILENO);
			close(pipes[j][1]);
		}
		else if ((com == length && j == length - 2) || \
			(com > 1 && com < length && com - 2 == j))
		{
			close(pipes[j][1]);
			dup2(pipes[j][0], STDIN_FILENO);
			close(pipes[j][0]);
		}
		else
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
		j++;
	}
}
