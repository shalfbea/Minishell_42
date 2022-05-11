/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:42:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/11 21:04:50 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_list	*parse_start(t_parser_data *data)
{
	t_command_list	*res;
	t_command_list	*cur;
	t_lexer			*arg;
	t_list			*argv;
	int				mode;

	if (!args)
		return (NULL);
	res = NULL;
	cur = NULL;
	argv = NULL;
	mode = 0;
	command_append(&res, &cur);
	while (args)
	{
		arg = (t_lexer *) args->content;
		if (arg->type < 3) //EDIT LATER
		{
			if (mode == 0)
				ft_lstadd_back(&argv, ft_lstnew((void *)arg->str));
			if (mode == REDIR_OUT)
			{
				cur->outfile = arg->str;
				mode = 0;
			}
			if (mode == REDIR_IN)
			{
				cur->infile = arg->str;
				mode = 0;
			}
		}
		else if (arg->type == REDIR_OUT)
		{
			cur->redirect_flag_outfile = 0;
			mode = REDIR_OUT;
		}
		else if (arg->type == REDIR_IN)
		{
			cur->redirect_flag_infile = 0;
			mode = REDIR_IN;
		}
		else if (arg->type == REDIR_APPEND)
		{
			cur->redirect_flag_outfile = 1;
			mode = REDIR_OUT;
		}
		else if (arg->type == REDIR_INSOURCE)
		{
			cur->redirect_flag_infile = 1;
			mode = REDIR_IN;
		}
		else if (arg->type == PIPE)
		{
			cur->argv = array_former(&argv);
			command_append(&res, &cur);
			mode = 0;
		}
		args = args->next;
	}
	cur->argv = argv_former(&argv);
	cur->
	return (res);
}

t_logical_groups	*parser(t_list *args)
{
	t_parser_data		data;
	t_logical_groups	*res;

	data.cur = NULL;
	data.res = NULL;
	data.arg = args;
	data.argv = NULL;
	data.mode = 0;
	data.redirect_flags = NULL;
	data.redirects = NULL;
	res = form_group(parse_start(&data));
	return (res);
}
