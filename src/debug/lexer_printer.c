/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:46:14 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:09:44 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*debug_types_bonus(char k)
{
	if (k == IF_AND)
		return ("if_and &&");
	else if (k == IF_OR)
		return ("if_or ||");
	else if (k == P_OPEN)
		return ("( parenthese open");
	else if (k == WILDCARD)
		return ("wildcard");
	return (NULL);
}

static char	*debug_types(char k)
{
	if (k == NO_QUOTE)
		return ("word");
	else if (k == QUOTES)
		return ("in quotes");
	else if (k == DOUBLE_QUOTES)
		return ("in double quotes");
	else if (k == REDIR_OUT)
		return ("redir out >");
	else if (k == REDIR_IN)
		return ("redir in <");
	else if (k == REDIR_APPEND)
		return ("redir append >>");
	else if (k == REDIR_INSOURCE)
		return ("redir insource <<");
	else if (k == PIPE)
		return ("pipe |");
	return (debug_types_bonus(k));
}

void	iter_printer(void *cur)
{
	printf("%s; Type: %s",
		((t_lexer *) cur)->str,
		debug_types((int)((t_lexer *)cur)->type));
	if (((t_lexer *) cur)->to_prev)
		printf("; This adds to prev.");
	printf("\n");
}

void	debug_lexer_printer(char *msg, t_list	*args)
{
	if (msg)
		printf("\n%s:\n\n", msg);
	ft_lstiter(args, iter_printer);
	printf("\n===================\n===================\n");
}
