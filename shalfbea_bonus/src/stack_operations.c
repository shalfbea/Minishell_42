/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:58:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 18:13:25 by shalfbea         ###   ########.fr       */
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
		return (NULL); //RAISE ERROR
	new_head->content = content; //may be not needed
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
