/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:03:30 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:12:40 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_malloc(int *n, int *tens, unsigned char *put_minus)
{
	int				tmp;
	int				len;
	char			*res;

	len = 2;
	*tens = 1;
	*put_minus = 0;
	if (*n < 0)
	{
		len++;
		*n *= -1;
		*put_minus = 1;
	}
	tmp = *n;
	while (tmp > 9)
	{
		tmp /= 10;
		len++;
		(*tens) *= 10;
	}
	res = (char *)malloc(sizeof(char) * (len));
	if (put_minus && res)
		*res = '-';
	return (res);
}

static char	ft_itoa_special_cases(int n, char **res)
{
	if (n == -2147483648)
	{
		*res = (char *)malloc(sizeof(char) * (12));
		if (!res)
		{
			*res = NULL;
			return (1);
		}
		ft_strlcpy(*res, "-2147483648", 12);
		return (1);
	}
	return (0);
}

/*
** Allocates (with malloc(3)) and returns a string
** representing the integer received as an argument.
** Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	int				tens;
	char			*res;
	char			*ret_res;
	unsigned char	put_minus;

	res = NULL;
	if (ft_itoa_special_cases(n, &res))
		return (res);
	res = ft_itoa_malloc(&n, &tens, &put_minus);
	if (!res)
		return (NULL);
	ret_res = res;
	if (put_minus)
		res++;
	while (tens > 0)
	{
		*res = (char)((n / tens) + '0');
		n %= tens;
		tens /= 10;
		res++;
	}
	*res = '\0';
	return (ret_res);
}
