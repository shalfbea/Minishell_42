/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:18:22 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 20:40:23 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_group	*group_new(t_list	*lst, char status)
{
	t_group	*res;

	res = (t_group *) malloc(sizeof(t_group));
	if (!res)
		return (NULL);
	res->args = lst;
	res->status = STATUS_UNDONE;
	if (!lst)
		res->status = status;
	return (res);
}

void	group_free(void *group_src)
{
	t_group	*group;

	group = (t_group *) group_src;
	if (!group)
		//return (NULL);
		return ;
	if (group->args)
		clear_lexer_lst(&(group->args));
	free(group);
	//return (NULL);
}

