/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:31:41 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 16:28:20 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  DESCRIPTION
**  The ft_memcpy() function copies n bytes from memory area src
**  to memory area dst.  If dst and src overlap, behavior is
**  undefined.  Applications in which dst and src might overlap
**  should use ft_memmove(3) instead.
**
**  RETURN VALUES
**  The ft_memcpy() function returns the original value of dst.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s_dst;
	char	*s_src;
	size_t	i;

	if ((dst == NULL && src == NULL) && n > 0)
		return (dst);
	i = 0;
	s_dst = (char *) dst;
	s_src = (char *) src;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		++i;
	}
	return (dst);
}
