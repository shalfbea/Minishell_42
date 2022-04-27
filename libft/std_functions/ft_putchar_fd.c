/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:58:46 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/16 18:13:42 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs the character ’c’ to the given file
** descriptor.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
