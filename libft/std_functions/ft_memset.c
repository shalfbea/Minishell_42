/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:24:20 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:07:38 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_memset() function writes len bytes of value c
** 	(converted to an unsigned char) to the string b.
**
** RETURN VALUES
**  The ft_memset() function returns its first argument.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) b;
	while (i < len)
	{
		str[i] = (unsigned char) c;
		++i;
	}
	return (b);
}
