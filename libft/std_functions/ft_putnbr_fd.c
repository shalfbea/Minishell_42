/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:10:52 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:14:52 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_putnbr_fd_cases(int *n, int fd)
{
	if (*n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (*n < 0)
	{
		write(fd, "-", 1);
		*n *= -1;
	}
	return (0);
}

/*
** Outputs the integer ’n’ to the given file
** descriptor.
*/
void	ft_putnbr_fd(int n, int fd)
{
	int		tmp;
	int		tens;
	char	cur;

	if (ft_putnbr_fd_cases(&n, fd))
		return ;
	tmp = n;
	tens = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		tens *= 10;
	}
	while (tens > 0)
	{
		cur = (char)(n / tens) + '0';
		write(fd, &cur, 1);
		n %= tens;
		tens /= 10;
	}
}
