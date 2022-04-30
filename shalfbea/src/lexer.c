/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:16:38 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/30 18:56:05 by shalfbea         ###   ########.fr       */
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
	{
		add_to_lexer(&(data->res), ft_substr(data->str, data->begin, data->i - data->begin), 0, data->after_quotes);
		//data->is_word = 0;
	}
	(data->i)++;
	data->begin = data->i;
	if (!((data->str)[data->i]))
		return (error_msg(QUOTES)); //raise error!
	//begin = *i;
	while ((data->str)[data->i] && (data->str)[data->i] != quote)
		++(data->i);
	if ((data->str)[data->i] != quote)
		return (error_msg(QUOTES)); //raise error!
	add_to_lexer(&(data->res), ft_substr(data->str, data->begin, data->i - data->begin), quote, (data->is_word) || data->after_quotes);
	data->after_quotes = 1;
	data->is_word = 0;
	//++(*i);
	return (0);
}

/*
char	check_specials(t_list	**res, size_t *begin, char *is_word, char *str)
{
	if (str[i] == '(' || str[i] == ')')
	{
		if (is_word)
		{
			is_word = 0;
			add_to_lexer(&res, ft_substr(str, begin, i - begin), 0);
		}
		add_to_lexer(&res, ft_substr(str, i, 1), 0);
	}
}
*/

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

t_list	*splitter(t_splitter_data *data)
{
	char	specials;

	while ((data->str)[++(data->i)])
	{
		if (ft_isspace(data->str[data->i]))
			data->after_quotes = 0;
		//if ((data->str)[(data->i)] == '\'' || (data->str)[(data->i)] == '"')
		specials = special_characters(&(data->str)[data->i]);
		if (specials)
		{
			if (quotes_breaker(data))
				return (clear_lexer_lst(&(data->res)));
			if (specials < 3)
			{
				if (data->is_word)
					add_to_lexer(&(data->res), ft_substr(data->str, data->begin, data->i - data->begin), 0, data->after_quotes);
				data->after_quotes = 0;
				data->is_word = 0;
				add_to_lexer(&(data->res), ft_substr(data->str, data->i, specials), 0, 0);
				data->i = data->i + specials - 1;
			}
		}
		else if (!ft_isspace(data->str[data->i]) && (!(data->is_word)) && data->str[data->i])
		{
			data->begin = data->i;
			data->is_word = 1;
			//data->after_quotes = 0;
		}
		else if (ft_isspace(data->str[data->i]) && data->is_word)
		{
			data->is_word = 0;
			add_to_lexer(&(data->res), ft_substr(data->str, data->begin, data->i - data->begin), 0, data->after_quotes);
			data->after_quotes = 0;
		}
	}
	if (data->is_word)
		add_to_lexer(&(data->res), ft_substr(data->str, data->begin, data->i - data->begin), 0, data->after_quotes);
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
	//data.in_quoutes = 0;
	data.after_quotes = 0;
	return (splitter(&data));
}
