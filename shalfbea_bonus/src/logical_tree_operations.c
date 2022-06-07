/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_tree_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:52:56 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/07 17:01:20 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical_tree	*lt_new(t_list	*args, char condition)
{
	t_logical_tree	*result;

	result = malloc(sizeof(t_logical_tree *));
	if (!result)
		return (NULL);
	result->args = args;
	result->child = NULL;
	result->next = NULL;
	result->condition = condition;
	return (result);
}

t_logical_tree	*lt_add_next(t_logical_tree **root, t_logical_tree *next_lt)
{
	if (!next_lt)
		return (*root);
	if (!(*root))
	{
		*root = next_lt;
		return (*root);
	}
	(*root)->next = next_lt;
	return ((*root)->next);
}

t_logical_tree	*lt_add_child(t_logical_tree **root, t_logical_tree *child_lt)
{
	if (!child_lt)
		return (*root);
	if (!(*root))
	{
		*root = child_lt;
		return (*root);
	}
	(*root)->child = child_lt;
	return ((*root)->child);
}
