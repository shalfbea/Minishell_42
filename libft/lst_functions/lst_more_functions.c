/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_more_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:48:55 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/28 14:49:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_content_swap(t_list *element_a, t_list *element_b)
{
	void	*tmp_content;

	if (!element_a || !element_b)
		return ;
	tmp_content = element_a->content;
	element_a->content = element_b->content;
	element_b->content = tmp_content;
}
