/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:14:23 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 18:20:32 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	quotes_breaker(t_splitter_data *data)
{
	char	quote;

	quote = (data->str)[data->i];
	if (quote != '\'' && quote != '\"')
		return (0);
	if (data->is_word)
		add_to_lexer(&(data->res), ft_substr(data->str, data->begin,
				data->i - data->begin), 0, data->after_quotes);
	(data->i)++;
	data->begin = data->i;
	if (!((data->str)[data->i]))
		return (error_msg(QUOTES)); //raise error!
	while ((data->str)[data->i] && (data->str)[data->i] != quote)
		++(data->i);
	if ((data->str)[data->i] != quote)
		return (error_msg(QUOTES)); //raise error!
	add_to_lexer(&(data->res), ft_substr(data->str, data->begin,
			data->i - data->begin), quote,
		(data->is_word) || data->after_quotes);
	data->after_quotes = 1;
	data->is_word = 0;
	return (0);
}

char	special_characters(char	*c)
{
	if (*c == '\'')
		return (3);
	if (*c == '\"')
		return (3);
	else if (*c == '>' && c[1] != '<')
		return (1);
	else if (*c == '<' && c[1] != '<')
		return (1);
	else if (*c == '>' && c[1] == '>')
		return (2);
	else if (*c == '<' && c[1] == '<')
		return (2);
	else if (*c == '|' && c[1] != '|')
		return (1);
	else if (*c == '&' && c[1] == '&')
		return (2);
	else if (*c == '|' && c[1] == '|')
		return (2);
	else if (*c == '(')
		return (1);
	else if (*c == ')')
		return (1);
	return (0);
}

char	special_handler(t_splitter_data *data, char specials)
{
	if (quotes_breaker(data))
	{
		clear_lexer_lst(&(data->res));
		return (1);
	}
	if (specials < 3)
	{
		if (data->is_word)
			add_to_lexer(&(data->res), ft_substr(data->str, data->begin,
					data->i - data->begin), 0, data->after_quotes);
		data->after_quotes = 0;
		data->is_word = 0;
		add_to_lexer(&(data->res), ft_substr(data->str, data->i,
				specials), 0, 0);
		data->i = data->i + specials - 1;
	}
	return (0);
}
