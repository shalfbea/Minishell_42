/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:01:43 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 17:02:50 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*s_dst;
	char		*last_dst;
	const char	*s_src;
	const char	*last_src;

	if (dst == NULL && src == NULL && len > 0)
		return (NULL);
	s_dst = (char *) dst;
	s_src = (char *) src;
	if (dst < src)
	{
		while (len--)
			*s_dst++ = *s_src++;
	}
	else
	{
		last_dst = s_dst + len - 1;
		last_src = s_src + len - 1;
		while (len--)
			*last_dst-- = *last_src--;
	}
	return ((void *) dst);
}
