/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:44:56 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/20 14:38:38by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_commands(t_command_list *commands, t_exec_env *in_exec)
{
	int	i;
	t_command_list	*tmp_cmd;
	t_fds	*tmp_in;
	if (g_ms_env.number_of_commands == 1 && check_builtin(commands->argv[0]) < 7)
		return (run_builtin(commands, in_exec));
	i = 0;
	tmp_cmd = commands;
	tmp_in = in_exec->first_fd;
	if (alloc_pids())
		return (ft_free(commands, in_exec));
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
	close_pipes(in_exec, g_ms_env.number_of_commands);
	if (ft_wait(in_exec))
		return (1);
	return (0);
}

void	ft_exec(t_command_list *cmd, t_exec_env *in_exec, int i)
{
	int	j;

	j = 1;
	create_pipeline(in_exec->_pipes, i, g_ms_env.number_of_commands);
	if (check_builtin(cmd->argv[0]) < 7)
		exit(run_builtin(cmd, in_exec));
	if (working_with_redirects(cmd, in_exec, i))
		exit(1);
	swap_filedescriptors(in_exec, i);
	if (check_cmd(&cmd->argv[0]))
		exit(127);
	execve((cmd->argv)[0], cmd->argv, g_ms_env.envp);
	exit(242);
}

void	swap_filedescriptors(t_exec_env *in_exec, int com)
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
	if (tmp_fd->infile != -55)
	{
		dup2(tmp_fd->infile, STDIN_FILENO);
		close(tmp_fd->infile);
	}
	if (tmp_fd->outfile != -55)
	{
		dup2(tmp_fd->outfile, STDOUT_FILENO);
		close(tmp_fd->outfile);
	}
}

void	create_pipeline(int	**pipes, int com, int length)
{
	int	j;

	j = 0;
	while (j < length - 1)//stdin:0, stdout:1
	{
		if ((com == 1 && j == 0) || (com > 1 && com < length && com - 1 == j))
		{
			close(pipes[j][0]);
			dup2(pipes[j][1], STDOUT_FILENO);
			close(pipes[j][1]);
		}
		else if ((com == length && j == length - 2) || (com > 1 && com < length && com - 2 == j))
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

int	ft_wait(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;
	int		i;

	i = 0;
	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		waitpid(g_ms_env.pids[i], &(tmp_fd->r_code), 0);
		if (WIFEXITED(tmp_fd->r_code))
			tmp_fd->r_code = WEXITSTATUS(tmp_fd->r_code);
		else
			tmp_fd->r_code = 1;
		if (tmp_fd->r_code == 242)
			return (ft_kill(in_exec));
		tmp_fd = tmp_fd->next_fd;
		i++;
	}
	return (0);
}

int	ft_kill(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;
	int		i;

	i = 0;
	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		kill(g_ms_env.pids[i], 2);
		tmp_fd = tmp_fd->next_fd;
		i++;
	}
	return (1);
}
