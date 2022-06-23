/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:42:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 14:29:25 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	form_current(t_parser_data *data, char end)
{
	g_ms_env.number_of_commands++;
	data->cur->argv = string_array_former(&(data->argv));
	data->cur->redirects = string_array_former(&(data->redirects));
	data->cur->redirect_flags = char_array_former(&(data->redirect_flags));
	if (!end)
		command_append(&(data->res), &(data->cur));
	data->mode = 0;
}

static void	parser_quotes_handle(t_parser_data *data)
{
	if (data->mode == 0)
		ft_lstadd_back(&(data->argv),
			ft_lstnew((void *) ft_strdup(data->arg->str)));
	else if (data->mode >= REDIR_OUT && data->mode <= REDIR_INSOURCE)
	{
		ft_lstadd_back(&(data->redirects),
			ft_lstnew((void *)ft_strdup(data->arg->str)));
		data->mode = 0;
	}
}

static char	parser_redirs_handle(t_parser_data *data)
{
	if (data->mode >= REDIR_OUT && data->arg->type <= REDIR_INSOURCE)
		return (1);
	ft_lstadd_back(&(data->redirect_flags),
		ft_lstnew_from_char(data->arg->type));
	data->mode = data->arg->type;
	return (0);
}

static t_command_list	*parse_start(t_parser_data *data)
{
	command_append(&(data->res), &(data->cur));
	while (data->args)
	{
		data->arg = (t_lexer *) data->args->content;
		if (data->arg->type >= NO_QUOTE && data->arg->type <= DOUBLE_QUOTES)
			parser_quotes_handle(data);
		else if (data->arg->type >= REDIR_OUT
			&& data->arg->type <= REDIR_INSOURCE)
		{
			if (parser_redirs_handle(data))
				return (error_and_clean(data, NULL));
		}
		else if (data->arg->type == PIPE)
		{
			if (!(data->argv))
				return (error_and_clean(data, NULL));
			form_current(data, 0);
		}
		data->args = data->args->next;
	}
	if (data->mode != NO_QUOTE)
		return (error_and_clean(data,
				"syntax error near unexpected token `newline'"));
	form_current(data, 1);
	return (data->res);
}

t_command_list	*parser(t_list *args)
{
	t_parser_data		data;
	t_command_list		*result;

	if (!args)
		return (NULL);
	g_ms_env.number_of_commands = 0;
	data.cur = NULL;
	data.res = NULL;
	data.args = args;
	data.argv = NULL;
	data.mode = 0;
	data.redirect_flags = NULL;
	data.redirects = NULL;
	result = parse_start(&data);
	if (!result)
		return (result);
	if (!(result->argv[0]) && !(result->redirect_flags[0]))
		return (clear_command_lst(&result));
	return (result);
}
