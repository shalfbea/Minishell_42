/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/27 21:06:10 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	error_msg(int mode)
{
	if (mode == QUOTES)
		printf("Error while parsing: quotes unmatched.");
	return (1);
}

char	quotes_breaker(char *str, size_t *i, t_list	**res)
{
	size_t	begin;
	char	quote;

	quote = str[*i];
	(*i)++;
	if (!str[*i])
		return (error_msg(QUOTES)); //raise error!
	begin = *i;
	while (str[*i] && str[*i] != quote)
		++(*i);
	if (str[*i] != quote)
		return (error_msg(QUOTES)); //raise error!
	add_to_lexer(res, ft_substr(str, begin, *i - begin), quote);
	//++(*i);
	return (0);
}

t_list	*splitter(char *str, size_t i, size_t begin)
{
	t_list			*res;
	unsigned char	is_word;

	res = NULL;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quotes_breaker(str, &i, &res))
				return (clear_lexer_lst(&res));
		}
		else if (!ft_isspace(str[i]) && (!is_word) && str[i])
		{
			begin = i;
			is_word = 1;
		}
		else if (ft_isspace(str[i]) && is_word)
		{
			is_word = 0;
			add_to_lexer(&res, ft_substr(str, begin, i - begin), 0);
		}
		printf("%zu", i);
	}
	printf("\n");
	if (is_word)
		add_to_lexer(&res, ft_substr(str, begin, i - begin), 0);
	return (res);
}

void	iter_printer(void *cur)
{
	char	*types[] = {"word", "in quotes", "in double quotes", "redir out >", "redir in <", "redir append >>", "redir insource <<", "pipe |", "if_and &&", "if_or ||"};

	printf("%s;type: %s\n", ((t_lexer *) cur)->str, types[(int) ((t_lexer *) cur)->type]);
}

int	prompt(void)
{
	char	*str;
	t_list	*args;

	str = NULL;
	//str = "\"\'lol\'\"";
	str = readline("MiniShell: ");
	if (!str)
		exit(0); // затычка
	args = splitter(str, -1, 0);
	ft_lstiter(args, iter_printer);
	printf("\n");
	//if (str)
	//	free(str);
	pause();
	return (0);
}
