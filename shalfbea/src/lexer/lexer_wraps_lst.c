/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wraps_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:41:36 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 18:03:01 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	type_detector(char	*str)
{
	if (str[0] == '>' && !str[1])
		return (REDIR_OUT);
	if (str[0] == '<' && !str[1])
		return (REDIR_IN);
	if (str[0] == '>' && str[1] == '>' && !str[2])
		return (REDIR_APPEND);
	if (str[0] == '<' && str[1] == '<' && !str[2])
		return (REDIR_INSOURCE);
	if (str[0] == '|' && !str[1])
		return (PIPE);
	if (str[0] == '&' && str[1] == '&' && !str[2])
		return (IF_AND);
	if (str[0] == '|' && str[1] == '|' && !str[2])
		return (IF_OR);
	if (str[0] == '(' && !str[1])
		return (P_OPEN);
	if (str[0] == ')' && !str[1])
		return (P_CLOSE);
	return (0);
}

void	add_to_lexer(t_list **lst, char *str, char type, char add_to_prev)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return ; //RAISE ERROR or exit
	lex->str = str;
	lex->to_prev = add_to_prev;
	if (type == '\'')
		type = QUOTES;
	else if (type == '"')
		type = DOUBLE_QUOTES;
	else if (type == NO_QUOTE)
		type = type_detector(str);
	lex->type = type;
	ft_lstadd_back(lst, ft_lstnew((void *) lex));
}

void	lexer_content_deleter(void *content)
{
	t_lexer	*lex;

	lex = (t_lexer *) content;
	if (!lex)
		return ;
	if (lex->str)
		free(lex->str);
	free(lex);
	return ;
}

t_list	*clear_lexer_lst(t_list **lst)
{
	ft_lstclear(lst, lexer_content_deleter);
	return (NULL);
}
