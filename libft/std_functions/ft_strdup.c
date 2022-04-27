/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:39:14 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:09:40 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The strdup() function allocates sufficient memory for a
**  copy of the string s1, does the copy, and returns a
**  pointer to it.  The pointer may subsequently be used
**  as an argument to the function free(3).
**
**  If insufficient memory is available, NULL is returned.
*/
char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s2 = (char *)malloc(sizeof(char) * size);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}
