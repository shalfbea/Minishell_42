/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:57:19 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:16:04 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts the number of elements in a list.
*/
int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
