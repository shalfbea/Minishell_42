/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:25:54 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:17:42 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes and frees the given element and every
** successor of that element, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur_elem;
	t_list	*next_elem;
	char	check;

	check = 1;
	if (*lst == NULL)
		return ;
	cur_elem = *lst;
	next_elem = *lst;
	while (check)
	{
		if (cur_elem->next)
			next_elem = cur_elem->next;
		else
			check = 0;
		del(cur_elem->content);
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
}
