/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:58:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/24 17:39:11 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function writes new content on top of stack
** and returns pointer to a new head of stack
*/
t_stack	*stack_push(t_stack *head, void *content)
{
	t_stack	*new_head;

	new_head = malloc(sizeof(t_stack));
	if (!new_head)
		return (NULL);
	new_head->content = content;
	new_head->next = head;
	return (new_head);
}

void	*stack_delete(t_stack **head)
{
	void	*content;
	t_stack	*tmp;

	if (!(*head))
		return (NULL);
	tmp = *head;
	content = tmp->content;
	*head = tmp->next;
	free (tmp);
	return (content);
}

void	stack_pop_to_lst(t_list **lst, t_stack **stack, t_list **to_add)
{
	t_lexer	*content;
	t_group	*group;

	content = (t_lexer *) stack_delete(stack);
	group = group_new(NULL, content->type);
	if (content)
	{
		if (*to_add)
		{
			lst_add_group(lst, *to_add, STATUS_UNDONE);
			*to_add = NULL;
		}
		if (group)
		{
			if (group->status)
				ft_lstadd_back(lst, ft_lstnew((void *) group));
			else
				group_free(&group);
		}
	}
}
