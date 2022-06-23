/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 21:14:16 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_group(t_list **lst, t_list *to_add, char status)
{
	ft_lstadd_back(lst, ft_lstnew((void *) group_new(to_add, status)));
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

void	polish_notation_operation_handler(t_list *args, t_list **res,
								t_list **group, t_stack **operators)
{
	if (*group)
	{
		lst_add_group(res, *group, STATUS_UNDONE);
		*group = NULL;
	}
	if (!(*operators))
		*operators = stack_push(*operators, args->content);
	else
	{
		while (*operators && ((t_lexer *)
				(*operators)->content)->type != P_OPEN)
			stack_pop_to_lst(res, operators, group);
		*operators = stack_push(*operators, args->content);
	}
}

t_list	*polish_notation_worker(t_list *args, t_list *res,
						t_list *group, t_stack *operators)
{
	t_lexer	*cur;

	while (args)
	{
		cur = (t_lexer *) args->content;
		if (cur->type == P_CLOSE)
		{
			while (((t_lexer *)operators->content)->type != P_OPEN)
				stack_pop_to_lst(&res, &operators, &group);
			stack_delete(&operators);
		}
		else if (cur->type == P_OPEN)
			operators = stack_push(operators, args->content);
		else if (cur->type == IF_OR || cur->type == IF_AND)
			polish_notation_operation_handler(args, &res, &group, &operators);
		else
			ft_lstadd_back(&group, ft_lstnew(args->content));
		args = args->next;
	}
	while (operators)
		stack_pop_to_lst(&res, &operators, &group);
	if (group)
		lst_add_group(&res, group, STATUS_UNDONE);
	return (res);
}

t_list	*to_polish_notation(t_list *args)
{
	if (!args)
		return (NULL);
	return (polish_notation_worker(args, NULL, NULL, NULL));
}
