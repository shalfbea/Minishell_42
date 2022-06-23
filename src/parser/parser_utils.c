/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:04:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 14:04:55 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_from_char(char c)
{
	t_list	*res;
	char	*tmp;

	res = ft_lstnew(NULL);
	tmp = (void *) malloc(sizeof(char));
	*tmp = c;
	res->content = (void *) tmp;
	return (res);
}

t_command_list	*error_and_clean(t_parser_data *data, char *error_msg)
{
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(data->arg->str, 2);
		ft_putendl_fd("'", 2);
	}
	ft_lstclear(&(data->argv), &no_delete);
	ft_lstclear(&(data->redirects), &no_delete);
	ft_lstclear(&(data->redirect_flags), &free);
	return (clear_command_lst(&(data->res)));
}
