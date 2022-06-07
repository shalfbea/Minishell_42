/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/07 20:14:16 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_logical_tree	*logic_parse_recursive(t_list	**args) //dont forget to look for head of args!
{
	t_lexer			*cur;
	t_list			*command_args;
	t_logical_tree	*result;

	result = lt_new(NULL, 0);
	command_args = NULL;
	while (*args)
	{
		cur = (t_lexer *) (*args)->content;
		if (cur->type == P_OPEN)
			lt_add_child(&result, logic_parser(&((*args)->next)));
		else if (cur->type == P_CLOSE)
			return (lt_new(command_args, 0));
		else if (cur->type == IF_AND || cur->type == IF_OR)
			lt_add_next(&result, logic_parser(&((*args)->next)));
		else
			add_to_lexer(&command_args, ft_strdup(cur->str), cur->type, cur->type);
		args = &((*args)->next);
	}
	result->args = command_args;
	return (result);
}
*/
/*
t_logical_tree	*logic_parser(t_list	**args)
{
	t_list	*args_copy;

	args_copy = args;
	lexer_unneeded_parentheses_remover(args);
	return (logic_parse_recursive(&args_copy));
}
*/

void	stack_pop_to_lst(t_list **lst, t_stack **stack)
{
	void	*content;

	content = stack_delete(stack);
	if (content)
		ft_lstadd_back(lst, ft_lstnew(content));
}

void	to_polish_notion(t_list **args_orignal)
{
	t_list	*args;
	t_list	*res;
	t_lexer *cur;
	t_stack *operators;

	args = *args_orignal;
	res = NULL;
	operators = NULL;
	while(args)
	{
		cur = (t_lexer *) args->content;
		if (cur->type == P_CLOSE)
		{
			while (((t_lexer *)operators->content)->type != P_OPEN)
				stack_pop_to_lst(&res, &operators);
			stack_delete(&operators);
		}
		else if (cur->type == P_OPEN)
			operators = stack_push(operators, args->content);
		else if (cur->type == IF_OR || cur->type == IF_AND)
		{
			if (!operators)
				operators = stack_push(operators, args->content);
			else
			{
				while (operators)
					stack_pop_to_lst(&res, &operators);
				operators = stack_push(operators, args->content);
			}
		}
		else
			ft_lstadd_back(&res, ft_lstnew(args->content));
		args = args->next;
	}
	while (operators)
		stack_pop_to_lst(&res, &operators);
	clear_lexer_lst(args_orignal, NULL);
	*args_orignal = res;
}
