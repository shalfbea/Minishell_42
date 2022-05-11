/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_groups.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:59:40 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/11 21:05:08 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical_groups	*form_group(t_command_list *commands_lst)
{
	t_logical_groups	*res;

	res = (t_logical_groups *) malloc(sizeof(t_logical_groups));
	if (!res)
		return (NULL);
	res->first_command = commands_lst;
	res->logical_flag	= 0;
	res->next_group = NULL;
	res->number_of_commands = 0;
	return (res);
}
