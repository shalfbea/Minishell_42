/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:49:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/06 20:24:19 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical_tree	*logic_parser(t_list	**args) //dont forget to look for head of args!
{
	t_lexer			*cur;
	t_list			*command_args;
	t_logical_tree	*result;

	result = NULL;
	command_args = NULL;
	while (args)
	{
		cur = (t_lexer *) (*args)->content;
		if (cur->type == P_OPEN)
			lt_add_child(&result, logic_parser((*args)->next));
		else if (cur->type == P_CLOSE)
			return (result);
		//....
		(*args) = (*args)->next;
	}
}
