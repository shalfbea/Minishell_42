/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:23:10 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:11:05 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a new
** string, which is the result of the concatenation
** of ’s1’ and ’s2’.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	k;
	size_t	len;

	if ((!s1) || (!s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *) malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
		res[k++] = s1[i++];
	i = 0;
	while (s2[i])
		res[k++] = s2[i++];
	res[k] = '\0';
	return (res);
}
