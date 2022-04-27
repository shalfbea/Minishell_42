/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:06:23 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:21:22 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs the string ’s’ to the given file
** descriptor, followed by a newline.
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	len;

	if (s == NULL)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
	write(fd, "\n", 1);
}
