/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:47:57 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/07 20:38:05 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	if (count < 0 || size < 0)
		return (NULL);
	bytes = malloc(size * count);
	if (!bytes)
		return (NULL);
	while (i < (size * count))
	{
		bytes[i] = '\0';
		++i;
	}
	return ((void *)bytes);
}
