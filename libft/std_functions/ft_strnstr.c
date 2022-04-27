/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:50:16 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:05:22 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**  The ft_strnstr() function locates the first occurrence of
** 	the null-terminated string needle in the string haystack,
** 	where not more than len characters are searched.
** 	Characters that appear after a `\0' character are not
** 	searched.
**
** RETURN VALUES
**  If needle is an empty string, haystack is returned;
**  if needle occurs nowhere in haystack, NULL is returned;
**  otherwise a pointer to the first character of the first
**  occurrence of needle is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *) haystack);
	if (!needle[0])
		return ((char *)haystack);
	if (needle_len < 1 || len < 0 )
		return (NULL);
	if (needle_len > len && haystack)
		return (NULL);
	i = 0;
	while (i <= (len - needle_len) && haystack[0])
	{
		if (haystack[0] == needle[0])
		{
			if (ft_strncmp(haystack, needle, needle_len) == 0)
				return (((char *)(haystack)));
		}
		++i;
		haystack++;
	}
	return (NULL);
}
