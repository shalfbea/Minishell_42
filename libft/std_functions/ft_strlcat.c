/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:43:10 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 17:12:41 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_strlcat() function copy and concatenate strings
**  with the same input parameters and output
**  result as snprintf(3)
**
**  strlcat() take the full size of the destination buffer and
**  guarantee NUL-termination if there is room.  Note that
**  room for the NUL should be included in dstsize
**
**  strlcat() appends string src to the end of dst.  It will
**  append at most dstsize - strlen(dst) - 1 characters.
**  It will then NUL-terminate, unless dstsize is 0 or the
**  original dst string was longer than dstsize (in practice
**  this should not happen as it means that either dstsize
**  is incorrect or that dst is not a proper string)
**
**  If the src and dst strings overlap, the behavior is undefined.
**
** RETURN VALUES
**  Like snprintf(3), ft_strlcat() functions return the
**  total length of the string they tried to create.
**  That means the initial length of dst plus the length of src
**
**  If the return value is >= dstsize, the output string has
**  been truncated.  It is the caller's responsibility
**  to handle this.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	if (dstsize < 1)
		return (dstsize + ft_strlen(src));
	while (dst[i] && i < dstsize)
		++i;
	dstsize--;
	while (src[++j])
	{
		if (i < dstsize)
			dst[i] = src[j];
		if (i == dstsize)
			dst[i] = '\0';
		++i;
	}
	if (i <= dstsize)
		dst[i] = '\0';
	return (i);
}
