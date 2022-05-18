/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:42:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/18 19:32:32 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	form_current(t_parser_data *data, char end)
{
	data->cur->argv = string_array_former(&(data->argv));
	data->cur->redirects = string_array_former(&(data->redirects));
	data->cur->redirect_flags = char_array_former(&(data->redirect_flags));
	if (!end)
		command_append(&(data->res), &(data->cur));
	data->mode = 0;
}

static t_list	*ft_lstnew_from_char(char c)
{
	t_list	*res;
	char	*tmp;

	res = ft_lstnew(NULL);
	tmp = (void *) malloc(sizeof(char));
	*tmp = c;
	res->content = (void *) tmp;
	return (res);
}

static t_command_list	*error_and_clean(t_parser_data *data)
{
	printf("syntax error near unexpected token `%s'\n", data->arg->str);
	ft_lstclear(&(data->argv), &no_delete);
	ft_lstclear(&(data->redirects), &no_delete);
	ft_lstclear(&(data->redirect_flags), &free);
	return(clear_command_lst(&(data->res)));
}

static t_command_list	*parse_start(t_parser_data *data)
{
	command_append(&(data->res), &(data->cur));
	while (data->args)
	{
		data->arg = (t_lexer *) data->args->content;
		if (data->arg->type >= NO_QUOTE && data->arg->type <= DOUBLE_QUOTES)
		{
			if (data->mode == 0)
				ft_lstadd_back(&(data->argv), ft_lstnew((void *)data->arg->str));
			else if (data->mode >= REDIR_OUT && data->mode <= REDIR_INSOURCE)
			{
				//data->cur->outfile = arg->str;
				ft_lstadd_back(&(data->redirects), ft_lstnew((void *)data->arg->str));
				data->mode = 0;
			}
		}
		else if (data->arg->type >= REDIR_OUT && data->arg->type <= REDIR_INSOURCE)
		{
			if (data->mode >= REDIR_OUT && data->arg->type <= REDIR_INSOURCE)
				return(error_and_clean(data));
			ft_lstadd_back(&(data->redirect_flags), ft_lstnew_from_char(data->arg->type));
			data->mode = data->arg->type;
		}
		else if (data->arg->type == PIPE)
		{
			if (!(data->argv))
				return (error_and_clean(data));
			form_current(data, 0);
		}
		data->args = data->args->next;
	}
	form_current(data, 1);
	return (data->res);
}

t_logical_groups	*parser(t_list *args)
{
	t_parser_data		data;
	t_logical_groups	*res;

	if(!args)
		return (NULL);
	data.cur = NULL;
	data.res = NULL;
	data.args = args;
	data.argv = NULL;
	data.mode = 0;
	data.redirect_flags = NULL;
	data.redirects = NULL;
	res = form_group(parse_start(&data));
	//builtin_checker(res);
	return (res);
}
