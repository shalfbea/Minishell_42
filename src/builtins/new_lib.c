/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:29:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/06/28 19:22:33 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip(const char *str, int *sign);

long	new_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	result;
	unsigned long		tmp_1;
	unsigned long		tmp_2;

	result = 0;
	sign = 1;
	i = skip(str, &sign);
	tmp_1 = 9223372036854775807;
	tmp_2 = 9223372036854775807;
	tmp_2 += 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i ++;
		if (((unsigned long)result > tmp_1 && sign == 1) \
			|| (unsigned long)result > tmp_2)
			break ;
	}
	if ((unsigned long)result > tmp_1 && sign == 1)
		return (-1);
	if ((unsigned long)result > tmp_2 && sign == -1)
		return (0);
	return ((long)result * sign);
}

static int	skip(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i ++;
	}
	return (i);
}

int	my_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s2[i] = ft_tolower(s2[i]);
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return ((unsigned char)s1[i]);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		if (!s1[i] || !s2[i])
			break ;
		i ++;
	}
	return (0);
}

void	skipp_n(char *str)
{
	unsigned int	i;

	i = 1;
	if (str[0] != '-')
		return ;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		str[2] = '\0';
}
