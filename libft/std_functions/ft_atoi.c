/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:30:34 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/26 16:49:40 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r')
		return (1);
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

static int	ft_atoi_helper(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

int	ft_atoi(const char *str)
{
	size_t	res;
	int		i;
	int		sign;

	sign = 1;
	res = 0;
	i = ft_atoi_helper(str, &sign);
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + str[i] - '0';
		++i;
		if ((sign > 0) && (res > 2147483647))
			return (-1);
		if ((sign < 0) && (res > 2147483648))
			return (0);
	}
	return ((int) res * sign);
}
