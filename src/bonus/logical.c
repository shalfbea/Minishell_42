/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/24 17:39:38 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*pn_error_and_clear(t_lexer *cur, t_list **res, t_stack **operators)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(cur->str, 2);
	ft_putendl_fd("'", 2);
	while (*operators)
		stack_delete(operators);
	ft_lstclear(res, group_free);
	return (NULL);
}

char	polish_notation_operation_handler(t_list *args, t_list **res,
								t_list **group, t_stack **operators)
{
	if (*group)
	{
		lst_add_group(res, *group, STATUS_UNDONE);
		*group = NULL;
	}
	else
		return (1);
	if (!(*operators))
		*operators = stack_push(*operators, args->content);
	else
	{
		while (*operators && ((t_lexer *)
				(*operators)->content)->type != P_OPEN)
			stack_pop_to_lst(res, operators, group);
		*operators = stack_push(*operators, args->content);
	}
	return (0);
}

void	polish_notation_post_work(t_list **res,
	t_list **group, t_stack **operators)
{
	while (*operators)
		stack_pop_to_lst(res, operators, group);
	if (group)
		lst_add_group(res, *group, STATUS_UNDONE);
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
		{
			if (polish_notation_operation_handler(args,
					&res, &group, &operators))
				return (pn_error_and_clear(cur, &res, &operators));
		}
		else
			ft_lstadd_back(&group, ft_lstnew(lexer_dup(args->content)));
		args = args->next;
	}
	polish_notation_post_work(&res, &group, &operators);
	return (res);
}

t_list	*to_polish_notation(t_list *args)
{
	if (!args)
		return (NULL);
	return (polish_notation_worker(args, NULL, NULL, NULL));
}
