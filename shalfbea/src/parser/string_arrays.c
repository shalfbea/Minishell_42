/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:18:58 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/23 17:47:20 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_delete(void *element)
{
	(void ) element;
}

char	**string_array_former(t_list	**array)
{
	char	**res;
	int		words;
	t_list	*tmp;
	int		i;

	words = ft_lstsize(*array);
	res = (char **) malloc(sizeof(char *) * (words + 1));
	tmp = *array;
	i = 0;
	while (i < words)
	{
		res[i] = (char *) tmp->content;
		tmp = tmp->next;
		++i;
	}
	res[i] = NULL;
	ft_lstclear(array, &no_delete);
	return (res);
}

void	string_array_cleaner(char	***array)
{
	int		i;

	if (!(*array))
		return ;
	i = 0;
	while ((*array)[i])
		free((*array)[i++]);
	if (*array)
		free(*array);
	*array = NULL;
}

/*
** Makes copy (throw ft_strdup) of string array
** and returns pointer to this copy.
** Can allocate more memory for pointers, if new_size
** param is bigger than actual size.
** Doesn't free input.
*/
char	**string_array_copy(char **array, uint more_size_option)
{
	char	**copy_of_array;
	int	len;

	len = 0;
	while (array[len++]);
	len += more_size_option;
	copy_of_array = (char **) malloc(sizeof(char *) * (len + 1));
	if (!copy_of_array)
		return (NULL);
	len = -1;
	char 	*tmp;
	while (array[++len])
	{
		tmp = ft_strdup(array[len]);
		copy_of_array[len] = tmp;
	}
	copy_of_array[len] = NULL;
	return (copy_of_array);
}
