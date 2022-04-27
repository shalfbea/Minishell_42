/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 22:09:00 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:12:54 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Applies the function ’f’ to each character of the
** string ’s’ to create a new string (with malloc(3))
** resulting from successive applications of ’f’.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	char	*ret_res;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	ret_res = res;
	i = 0;
	while (*s)
		*res++ = f(i++, *s++);
	*res = '\0';
	return (ret_res);
}
