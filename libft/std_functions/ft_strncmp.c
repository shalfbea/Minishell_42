/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:29:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:00:28 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_strncmp() function lexicographically compare the
**  null-terminated strings s1 and s2.
**
**  The ft_strncmp() function compares not more than n characters.
**  Because ft_strncmp() is designed for comparing strings rather
**  than binary data, characters that appear after a
**  `\0' character are not compared.
**
** RETURN VALUES
**  The ft_strncmp() functions return an integer greater than,
**  equal to, or less than 0, according as the string s1 is
**  greater than, equal to, or less than the string s2.
**  The comparison is done using unsigned characters,
**  so that `\200' is greater than `\0'.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] == s2[i]) && s1[i] && s2[i])
		++i;
	if (i == n)
		return ((int) 0);
	return ((unsigned char)s1[i] - s2[i]);
}
