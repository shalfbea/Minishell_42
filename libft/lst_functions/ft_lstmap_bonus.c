/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:56:30 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:18:22 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstmap_free(t_list **lst, void (*del)(void *))
{
	t_list	*cur_elem;
	t_list	*next_elem;
	char	check;

	check = 1;
	if (*lst == NULL)
		return (NULL);
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
	return (NULL);
}

/*
** Iterates the list ’lst’ and applies the function
** ’f’ to the content of each element. Creates a new
** list resulting of the successive applications of
** the function ’f’. The ’del’ function is used to
** delete the content of an element if needed.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_head;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	new_head = new_list;
	if (!new_list)
		return (ft_lstmap_free(&new_list, del));
	while (lst->next)
	{
		lst = lst->next;
		new_list->next = ft_lstnew(f(lst->content));
		if (new_list == NULL)
			return (ft_lstmap_free(&new_head, del));
		new_list = new_list->next;
	}
	return (new_head);
}
