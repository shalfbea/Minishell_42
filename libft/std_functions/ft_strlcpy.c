/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:28:00 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 16:43:34 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_strlcpy() function copy and concatenate strings with the same
** 	input parameters and output result as snprintf(3).
**
**  ft_strlcpy() take the full size of the destination buffer and guarantee
** 	NUL-termination if there is room.  Note that room for
**  the NUL should be included in dstsize.
**
**  ft_strlcpy() copies up to dstsize - 1 characters from the string src
**  to dst, NUL-terminating the result if dstsize is not 0.
**
**  If the src and dst strings overlap, the behavior is undefined.
**
** RETURN VALUES
**  the ft_strlcpy() function return the total length of the string they
**  tried to create.  For strlcpy() that means the length of src.
**
**  If the return value is >= dstsize, the output string has been
**  truncated. It is the caller's responsibility to handle this.
**
*/
size_t	ft_strlcpy(char *dst, const char *src,
					size_t dstsize)
{
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
	if (dstsize <= 0)
		return (size_src);
	i = 0;
	while (i < size_src && i < dstsize - 1)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (size_src);
}
