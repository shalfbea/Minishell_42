/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:16:38 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 19:52:44 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_word(t_splitter_data *data)
{
	data->begin = data->i;
	data->is_word = 1;
}

static void	end_word(t_splitter_data *data)
{
	char	type;

	type = 0;
	data->is_word = 0;
	if (data->res)
	{
		if (((t_lexer *)((ft_lstlast(data->res))->content))->type
			== REDIR_INSOURCE)
			type = QUOTES;
	}
	add_to_lexer(&(data->res), ft_substr(data->str, data->begin,
			data->i - data->begin), type, data->after_quotes);
	data->after_quotes = 0;
}

static t_list	*splitter(t_splitter_data *data)
{
	char	specials;

	while ((data->str)[++(data->i)])
	{
		specials = special_characters(&(data->str)[data->i]);
		if (specials)
		{
			if (special_handler(data, specials))
				return (NULL);
		}
		else if (wildcard_handler(data) == 1)
			add_to_lexer(&(data->res), ft_strdup("*"), WILDCARD, 0);
		else if (!ft_isspace(data->str[data->i])
			&& (!(data->is_word)) && data->str[data->i])
			start_word(data);
		else if (ft_isspace(data->str[data->i]) && data->is_word)
			end_word(data);
		if (ft_isspace(data->str[data->i]))
			data->after_quotes = 0;
	}
	if (data->is_word)
		end_word(data);
	return (data->res);
}

t_list	*lexer(char *str)
{
	t_splitter_data	data;

	data.begin = 0;
	data.i = -1;
	data.is_word = 0;
	data.res = NULL;
	data.str = str;
	data.after_quotes = 0;
	return (splitter(&data));
}
