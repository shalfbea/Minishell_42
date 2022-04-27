/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:10:10 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:10:34 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a substring
** from the string ’s’.
** The substring begins at index ’start’ and is of
** maximum size ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*copy;
	size_t	real_len;

	if (len < 0 || s == NULL)
		return (NULL);
	i = -1;
	while (++i < start && *s)
		s++;
	real_len = ft_strlen(s);
	if (real_len < len)
		len = real_len;
	copy = (char *) malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		copy[i] = s[i];
		++i;
	}
	copy[i] = '\0';
	return (copy);
}
