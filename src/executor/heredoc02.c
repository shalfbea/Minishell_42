/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:41 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/25 15:26:43 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_heredoc(t_command_list *cmd)
{
	int	i;
	int	num;
	char	*name;

	num = 1;
	while (cmd)
	{
		i = 0;
		while ((cmd->redirects)[i])
		{
			if ((cmd->redirect_flags)[i] == REDIR_INSOURCE)
			{
				name = create_name(num);
				if (!name)
					return (1);
				unlink(name);
				free(name);
				break ;
			}
			i++;
		}
		num++;
		cmd =cmd->next_command;
	}
	return (1);
}
