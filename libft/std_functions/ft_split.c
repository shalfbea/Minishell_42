/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:42:19 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:11:51 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_word_count(char const *s, char c)
{
	size_t			words;
	unsigned char	is_word;

	is_word = 0;
	words = 1;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_word)
			{
				words++;
				is_word = 1;
			}
		}
		if (*s == c && is_word)
			is_word = 0;
		s++;
	}
	return (words);
}

static char	*ft_split_make_word(char const *s, size_t begin, size_t end)
{
	char			*cur_word;
	size_t			i;

	i = 0;
	cur_word = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (!cur_word)
		return (NULL);
	while (begin <= end)
		cur_word[i++] = s[begin++];
	cur_word[i] = '\0';
	return (cur_word);
}

static char	**ft_split_make_words(char const *s, char c, char **res,
									size_t begin)
{
	size_t			end;
	unsigned char	is_word;
	size_t			i;

	end = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] != c) && (!is_word))
		{
			begin = i;
			is_word = 1;
		}
		if (s[i] == c && is_word)
		{
			is_word = 0;
			*res = ft_split_make_word(s, begin, end);
			res++;
		}
		if (is_word)
			end = i;
	}
	if (is_word)
		*res = ft_split_make_word(s, begin, end);
	return (res);
}

static char	**ft_split_res_free(char **res, size_t words)
{
	size_t	i;

	i = 0;
	while (i < (words - 1))
		free(res[i++]);
	free(res);
	return (NULL);
}

/*
** Allocates (with malloc(3)) and returns an array
** of strings obtained by splitting ’s’ using the
** character ’c’ as a delimiter. The array must be
** ended by a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;
	size_t	i;

	if (s == NULL)
		return (NULL);
	words = ft_split_word_count(s, c);
	res = (char **) malloc(sizeof(char *) * words);
	if (!res)
		return (NULL);
	if (words > 1)
		ft_split_make_words(s, c, res, (size_t) 0);
	res[(words - 1)] = NULL;
	i = 0;
	while (i < (words - 1))
	{
		if (res[i++] == NULL)
			return (ft_split_res_free(res, words));
	}
	return (res);
}
