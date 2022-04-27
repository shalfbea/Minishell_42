/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 22:19:23 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:13:19 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Applies the function f to each character of the
** string passed as argument, and passing its index
** as first argument. Each character is passed by
** address to f to be modified if necessary
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (*s)
		f(i++, s++);
}
