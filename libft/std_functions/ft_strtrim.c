/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:31:36 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:11:24 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strtrim_find(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_strtrim_find_begin_pos(char const *s1, char const *set)
{
	size_t	i;

	if (!(*set))
		return (0);
	i = 0;
	while (ft_strtrim_find(set, s1[i]))
		++i;
	return (i);
}

static size_t	ft_strtrim_find_end_pos(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	if (i > 0)
		i--;
	if (!(*set))
		return (i);
	while (ft_strtrim_find(set, s1[i]) && i > 0)
		--i;
	return (i);
}

static size_t	ft_strtrim_len(size_t begin, size_t end)
{
	if (begin > end)
		return (1);
	if (begin == end)
		return (2);
	return (end - begin + 2);
}

/*
** Allocates (with malloc(3)) and returns a copy of
** ’s1’ with the characters specified in ’set’ removed
** from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*res_ans;
	size_t	begin;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	begin = ft_strtrim_find_begin_pos(s1, set);
	end = ft_strtrim_find_end_pos(s1, set);
	res = (char *) malloc(sizeof(char) * (ft_strtrim_len(begin, end)));
	if (!res)
		return (NULL);
	res_ans = res;
	while (s1[begin] && begin <= end)
	{
		*res = s1[begin];
		res++;
		begin++;
	}
	*res = '\0';
	return (res_ans);
}
