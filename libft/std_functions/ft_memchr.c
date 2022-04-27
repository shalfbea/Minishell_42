/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:20:22 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:20:28 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The memchr() function locates the first occurrence of c
**  (converted to an unsigned char) in string s.
**
** RETURN VALUES
**  The memchr() function returns a pointer to the byte
**  located, or NULL if no such byte exists within n bytes.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	to_find;
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	to_find = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (*str == to_find)
			return ((void *)str);
		str++;
		i++;
	}
	return (NULL);
}
