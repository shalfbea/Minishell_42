/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:56:33 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:16:25 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the last element of the list.
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
