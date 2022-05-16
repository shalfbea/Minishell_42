/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wraps_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:41:36 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/16 16:45:27 by shalfbea         ###   ########.fr       */
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

t_list	*lst_new_lex(char	*str, char type, char add_to_prev)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL); //RAISE ERROR or exit
	lex->str = str;
	lex->type = type;
	lex->to_prev = add_to_prev;
	return(ft_lstnew((void *) lex));
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

