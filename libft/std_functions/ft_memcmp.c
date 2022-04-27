/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:34:05 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:06:33 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The memcmp() function compares byte string s1 against
** 	byte string s2.  Both strings are assumed to be
** 	n bytes long.
**
** RETURN VALUES
**  The memcmp() function returns zero if the two strings
** 	are identical, otherwise returns the difference between
** 	the first two differing bytes (treated as unsigned char
** 	values, so that `\200' is greater than `\0', for example).
**  Zero-length strings are always identical.  This behavior
** 	is not required by C and portable code should only depend
** 	on the sign of the returned value.
**
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while ((i < n) && (str1[i] == str2[i]))
		++i;
	if (i == n)
		return ((int) 0);
	return ((unsigned char)str1[i] - str2[i]);
}
