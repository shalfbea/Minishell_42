/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:13:16 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/22 16:20:36 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_array_former(t_list **array)
{
	int		size;
	int		i;
	char	*res;
	t_list	*tmp;

	tmp = *array;
	size = ft_lstsize(tmp);
	res = (char *) malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		res[i] = ((char *)tmp->content)[0];
		tmp = tmp->next;
	}
	res[i] = '\0';
	ft_lstclear(array, &free);
	return (res);
}

