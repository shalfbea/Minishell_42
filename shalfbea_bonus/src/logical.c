/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 18:02:01 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_lstadd_back(lst, ft_lstnew((void *) group_new(*to_add, STATUS_UNDONE)));
			//clear_lexer_lst(to_add);
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

t_list	*to_polish_notation(t_list *args)
{
	t_list	*res;
	t_list	*group;
	t_lexer *cur;
	t_stack *operators;

	res = NULL;
	group = NULL;
	operators = NULL;
	if (!args)
		return (NULL);
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
		{
			if (group)
			{
				ft_lstadd_back(&res, ft_lstnew((void *) group_new(group, STATUS_UNDONE)));
			//clear_lexer_lst(&group);
				group = NULL;
			}
			if (!operators)
				operators = stack_push(operators, args->content);
			else
			{
				while (operators && ((t_lexer *) operators->content)->type != P_OPEN)
					stack_pop_to_lst(&res, &operators, &group);
				operators = stack_push(operators, args->content);
			}
		}
		else
			ft_lstadd_back(&group, ft_lstnew(args->content));
		args = args->next;
		//debug_lexer_printer(cur->str, operators);
	}
	while (operators)
		stack_pop_to_lst(&res, &operators, &group);
	if (group)
		ft_lstadd_back(&res, ft_lstnew((void *) group_new(group, STATUS_UNDONE)));
	return (res);
}
