/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/16 20:22:46 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - s2[i]);
}

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
