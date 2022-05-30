/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:26:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/28 22:16:19by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	working_with_redirects(t_command_list *cmd, t_exec_env *in_exec, int num)
{
	t_fds	*tmp_fd;
	int		j;

	j = 1;
	tmp_fd = in_exec->first_fd;
	while (j < num)
	{
		tmp_fd = tmp_fd->next_fd;
		j++;
	}
	if (check_files(cmd, tmp_fd, num))
		return (1);
	return (0);
}

int	check_files(t_command_list *cmd, t_fds *tmp_fd, int num)
{
	int	j;
	char *name;

	j = 0;
	while (cmd->redirects[j])
	{
		if (cmd->redirect_flags[j] == REDIR_OUT || cmd->redirect_flags[j] == REDIR_APPEND)
		{
			if (tmp_fd->outfile != NO_FILE)
				close(tmp_fd->outfile);
			if (cmd->redirect_flags[j] == REDIR_OUT)
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				tmp_fd->outfile = open(cmd->redirects[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp_fd->outfile == -1)
				return (put_error(cmd->redirects[j], 1));
		}
		else if (cmd->redirect_flags[j] == REDIR_IN || cmd->redirect_flags[j] == REDIR_INSOURCE)
		{
			if (tmp_fd->infile != NO_FILE)
				close(tmp_fd->infile);
			if (tmp_fd->hd_flag != j && cmd->redirect_flags[j] == REDIR_IN)
				tmp_fd->infile = open(cmd->redirects[j], O_RDONLY);
			else if (tmp_fd->hd_flag == j && cmd->redirect_flags[j] == REDIR_INSOURCE)
			{
				name = create_name(num);
				if (!name)
					return (1);
				tmp_fd->infile = open(name, O_RDONLY);
				free(name);
			}
			else
				tmp_fd->infile = NO_FILE;
			if (tmp_fd->infile == -1)
				return (put_error(cmd->redirects[j], 1));
		}
		j++;
	}
	return (0);
}

int	put_error(char *name, char flag)
{
	char	*str;
	int		length;

	if (flag == ERR_FEW_ARG)
		str = "too few arguments";
	else if (flag == ERR_MANY_ARG)
		str = "too many arguments";
	else if (flag == ERR_EXPORT || flag == ERR_UNSET)
		str = "not a valid identifier";
	else if (flag == ERR_EXIT)
		str = "numeric argument required";
	else if (flag)
		str = strerror(errno);
	else
		str = "command not found";
	length = ft_strlen(name);
	write(STDERR_FILENO, "minishell: ", 11);
	if (flag == ERR_CD)
		write(STDERR_FILENO, "cd: ", 4);
	else if (flag == ERR_EXPORT)
		write(STDERR_FILENO, "export: `", 9);
	else if (flag == ERR_UNSET)
		write(STDERR_FILENO, "unset: `", 8);
	else if (flag == ERR_EXIT)
		write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, name, length);
	if (flag == ERR_EXPORT || flag == ERR_UNSET)
		write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, ": ", 2);
	length = ft_strlen(str);
	write(STDERR_FILENO, str, length);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
