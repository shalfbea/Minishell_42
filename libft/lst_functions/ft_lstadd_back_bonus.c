/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:16:50 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:16:56 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds the element ’new’ at the end of the list.
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur;

	cur = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
