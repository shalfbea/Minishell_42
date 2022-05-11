/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:36:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/11 17:36:50 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_realloc(char *result, unsigned int *size, int mod)
{
	char			*tmp;

	if (mod)
	{
		tmp = (char *)malloc(sizeof(char) * (*size));
		if (!tmp)
			return ((void *)0);
		tmp[0] = -1;
	}
	else
		tmp = my_realloc_two(result, size);
	return (tmp);
}

char	*my_realloc_two(char *result, unsigned int *size)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (*size * 2));
	if (!tmp)
	{
		free(result);
		return ((void *)0);
	}
	while (i < *size)
	{
		tmp[i] = result[i];
		i++;
	}
	*size = *size * 2;
	free(result);
	return (tmp);
}
