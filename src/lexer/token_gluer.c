/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gluer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:58 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/27 18:25:24 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_sticky_append(t_list **res, t_list **cur, t_lexer *lexical)
{
	char	*tmp;

	if (lexical->type == DOUBLE_QUOTES || lexical->type == QUOTES)
		lexical->type = NO_QUOTE;
	if (*res == NULL)
	{
		*cur = lst_new_lex(ft_strdup(lexical->str), lexical->type, 0);
		*res = *cur;
	}
	else
	{
		if (lexical->to_prev)
		{
			tmp = ((t_lexer *)(*cur)->content)->str;
			((t_lexer *)(*cur)->content)->str = ft_strjoin(tmp, lexical->str);
			if (tmp)
				free(tmp);
		}
		else
		{
			(*cur)->next = lst_new_lex(ft_strdup(lexical->str),
					lexical->type, 0);
			*cur = (*cur)->next;
		}
	}
}

static char	check_if_glue_needed(t_list *args)
{
	while (args)
	{
		if (((t_lexer *) args->content)->to_prev)
			return (1);
		if (!(((t_lexer *) args->content)->str)[0])
			return (1);
		args = args->next;
	}
	return (0);
}

void	token_gluer(t_list **args)
{
	t_list	*cur_args;
	t_list	*res;
	t_list	*res_cur;

	cur_args = *args;
	res = NULL;
	if (!check_if_glue_needed(*args))
		return ;
	while (cur_args)
	{
		if (cur_args->content)
		{
			if ((((t_lexer *) cur_args->content)->str)[0]
				|| (((t_lexer *) cur_args->content)->type) == DOUBLE_QUOTES)
				lst_sticky_append(&res, &res_cur,
					(t_lexer *) cur_args->content);
		}
		cur_args = cur_args->next;
	}
	clear_lexer_lst(args);
	*args = res;
}
