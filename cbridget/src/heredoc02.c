/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:47:41 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/13 13:17:39 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_heredoc(t_command_list *cmd)
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
			if ((cmd->redirect_flags)[i] == 3)
			{
				name = create_name(num);
				if (!name)
					return ;
				unlink(name);
				free(name);
				break ;
			}
			i++;
		}
		num++;
		cmd =cmd->next_command;
	}
}
