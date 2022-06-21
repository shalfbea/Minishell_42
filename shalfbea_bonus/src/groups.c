/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:18:22 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/21 20:29:51 by shalfbea         ###   ########.fr       */
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

t_group	*group_free(t_group **group)
{
	if (!(*group))
		return (NULL);
	if ((*group)->args)
		clear_lexer_lst(&((*group)->args));
	free(*group);
	*group = NULL;
	return (NULL);
}
