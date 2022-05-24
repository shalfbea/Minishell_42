/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_groups.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:59:40 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/18 19:42:30 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical_groups	*form_group(t_command_list *commands_lst)
{
	t_logical_groups	*res;

	if (!commands_lst)
		return (NULL);
	res = (t_logical_groups *) malloc(sizeof(t_logical_groups));
	if (!res)
		return (NULL);
	res->first_command = commands_lst;
	res->logical_flag	= 0;
	res->next_group = NULL;
	res->number_of_commands = 1; //CHANGE IT
	return (res);
}

t_logical_groups	*clear_groups(t_logical_groups **lst)
{
	t_logical_groups	*cur_elem;
	t_logical_groups	*next_elem;
	char			check;

	check = 1;
	if (*lst == NULL)
		return (NULL);
	cur_elem = *lst;
	next_elem = *lst;
	while (check)
	{
		if (cur_elem->next_group)
			next_elem = cur_elem->next_group;
		else
			check = 0;
		clear_command_lst(&(cur_elem->first_command));
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
	return (NULL);
}


