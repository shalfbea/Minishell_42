/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:44:56 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/16 22:19:42 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_commands(t_minishell_environment *min_environment, t_logical_groups *group, t_exec_env *in_exec)
{
	int	i;
	t_command_list	*tmp_cmd;
	t_fds	*tmp_in;
	if (group->number_of_commands == 1 && check_builtin(min_environment->builtin_names, group->first_command->argv[0]) < 7)
		return (run_builtin(min_environment, group->first_command, in_exec));
	i = 0;
	tmp_cmd = group->first_command;
	tmp_in = in_exec->first_fd;
	while (i < group->number_of_commands)
	{
		tmp_in->pid_com = fork();
		if (tmp_in->pid_com < 0)
			return (ft_free(group, in_exec));
		if (tmp_in->pid_com == 0)
			ft_exec(min_environment, tmp_cmd, in_exec, i + 1);
		tmp_cmd = tmp_cmd->next_command;
		tmp_in = tmp_in->next_fd;
		i++;
	}
	close_pipes(in_exec, group->number_of_commands);
	if (ft_wait(in_exec))
		return (1);
	return (0);
}

void	ft_exec(t_minishell_environment *min_environment, t_command_list *cmd, t_exec_env *in_exec, int i)
{
	int	j;

	j = 1;
	create_pipeline(in_exec->_pipes, i, in_exec->num_com);
	if (working_with_redirects(cmd, in_exec, i))
		exit(1);
	swap_filedescriptors(in_exec, i);
	if (check_builtin(min_environment->builtin_names, cmd->argv[0]) < 7)
		exit(run_builtin(min_environment, cmd, in_exec));
	if (check_cmd(&((cmd->argv)[0]), min_environment->envp))
		exit(127);
	execve((cmd->argv)[0], cmd->argv, min_environment->envp);
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

	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		waitpid(tmp_fd->pid_com, &(tmp_fd->r_code), 0);
		if (WIFEXITED(tmp_fd->r_code))
			tmp_fd->r_code = WEXITSTATUS(tmp_fd->r_code);
		else
			tmp_fd->r_code = 1;
		if (tmp_fd->r_code == 242)
			return (ft_kill(in_exec));
		tmp_fd = tmp_fd->next_fd;
	}
	return (0);
}

int	ft_kill(t_exec_env *in_exec)
{
	t_fds	*tmp_fd;

	tmp_fd = in_exec->first_fd;
	while (tmp_fd)
	{
		kill(tmp_fd->pid_com, 2);
		tmp_fd = tmp_fd->next_fd;
	}
	return (1);
}
