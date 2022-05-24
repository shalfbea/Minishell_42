/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unneeded_builtin_checker.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/22 18:12:49 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	builtin_definer(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (2);
	else if (!ft_strcmp(str, "pwd"))
		return (3);
	else if (!ft_strcmp(str, "export"))
		return (4);
	else if (!ft_strcmp(str, "unset"))
		return (5);
	else if (!ft_strcmp(str, "env"))
		return (6);
	else if (!ft_strcmp(str, "exit"))
		return (7);
	return (0);
}

void	builtin_checker(t_logical_groups	*groups)
{
	t_command_list	*commands;

	while (groups)
	{
		commands = groups->first_command;
		while (commands)
		{
			if ((commands->argv)[0])
				commands->build_in_flag = builtin_definer((commands->argv)[0]);
			commands = commands->next_command;
		}
		groups = groups->next_group;
	}

}
