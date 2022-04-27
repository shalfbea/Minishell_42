/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:28:38 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 17:16:07 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_strchr() function locates the first occurrence of c
**  (converted to a char) in the string pointed to by s.
**  The terminating null character is considered to be part
**  of the string; therefore if c is `\0', the functions
**  locate the terminating `\0'.
**
** RETURN VALUES
**  The functions strchr() and strrchr() return a pointer to
**  the located character, or NULL if the character does not
**  appear in the string.
*/
char	*ft_strchr(const char *s, int c)
{
	char	*cur;
	char	to_find;

	cur = (char *) s;
	to_find = (char) c;
	while (*cur)
	{
		if (*cur == to_find)
			return (cur);
		++cur;
	}
	if (to_find == '\0')
		return (cur);
	return (NULL);
}
