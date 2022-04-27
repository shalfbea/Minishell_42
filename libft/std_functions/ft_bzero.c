/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:17:52 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 16:27:29 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
** The ft_bzero() function writes n zeroed bytes to the string s.
** If n is zero, bzero() does nothing.
*/
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) s;
	while (i < n)
	{
		str[i] = '\0';
		++i;
	}
}
