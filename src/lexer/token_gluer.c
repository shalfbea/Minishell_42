/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gluer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:56:58 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/28 17:39:15 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_sticky_append_work(t_list **res, t_list **cur, t_lexer *lexical)
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

static void	lst_sticky_append(t_list *cur_args,
	t_list **res, t_list **res_cur, char *skip)
{
	if ((((t_lexer *) cur_args->content)->str)[0]
		|| (((t_lexer *) cur_args->content)->type) == DOUBLE_QUOTES)
	{
		if (*skip)
			((t_lexer *) cur_args->content)->to_prev = 0;
		lst_sticky_append_work(res, res_cur,
			(t_lexer *) cur_args->content);
			*skip = 0;
	}
	else
		*skip = 1;
}

void	token_gluer(t_list **args)
{
	t_list	*cur_args;
	t_list	*res;
	t_list	*res_cur;
	char	skip;

	skip = 0;
	cur_args = *args;
	res = NULL;
	while (cur_args)
	{
		if (cur_args->content)
			lst_sticky_append(cur_args, &res, &res_cur, &skip);
		cur_args = cur_args->next;
	}
	clear_lexer_lst(args);
	*args = res;
}
