/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:28:32 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/18 19:06:07 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_command(t_command_list *elem)
{
	if (elem->redirect_flags)
		free(elem->redirect_flags);
	string_array_cleaner(elem->argv);
	string_array_cleaner(elem->redirects);
}

t_command_list	*clear_command_lst(t_command_list **lst)
{
	t_command_list	*cur_elem;
	t_command_list	*next_elem;
	char			check;

	check = 1;
	if (*lst == NULL)
		return (NULL);
	cur_elem = *lst;
	next_elem = *lst;
	while (check)
	{
		if (cur_elem->next_command)
			next_elem = cur_elem->next_command;
		else
			check = 0;
		clear_command(cur_elem);
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
	return (NULL);
}

t_command_list	*new_command(void)
{
	t_command_list	*list;

	list = malloc(sizeof(t_command_list));
	if (!list)
		return (NULL);
	list->redirect_flags = NULL;
	list->redirects = NULL;
	list->argv = NULL;
	list->next_command = NULL;
	return (list);
}

void	command_append(t_command_list **lst, t_command_list **cur)
{
	if (*lst == NULL)
	{
		*cur = new_command();
		*lst = *cur;
	}
	else
	{
		(*cur)->next_command = new_command();
		*cur = (*cur)->next_command;
	}
}
