/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:05:56 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:06:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_groups_print_operator(t_group *cur)
{
	char	*s;

	s = NULL;
	if (cur->status == IF_AND)
		s = ft_strdup("&&");
	if (cur->status == IF_OR)
		s = ft_strdup("||");
	if (s)
		printf("operator: %s\n", s);
	else
		printf("operator: %c : %d\n", cur->status, cur->status);
	if (s)
		free(s);
}

void	debug_groups_printer(t_list	*group_lst)
{
	t_group	*cur;
	uint	group_num;

	group_num = 0;
	while (group_lst)
	{
		cur = (t_group *) group_lst->content;
		if (cur->args)
		{
			printf("-> Group %d:\n", group_num++);
			debug_lexer_printer(NULL, cur->args);
		}
		else
			debug_groups_print_operator(cur);
		group_lst = group_lst->next;
	}
}
