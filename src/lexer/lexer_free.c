/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:31:47 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/16 16:49:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_content_deleter(void *content)
{
	t_lexer	*lex;

	lex = (t_lexer *) content;
	if (!lex)
		return ;
	if (lex->str && !(lex->type >= NO_QUOTE && lex->type <= DOUBLE_QUOTES))
	//if (lex->str)
		free(lex->str);
	free(lex);
	return ;
}

void	lexer_content_free_all(void *content)
{
	t_lexer	*lex;

	lex = (t_lexer *) content;
	if (!lex)
		return ;
	//if (lex->str && !(lex->type >= NO_QUOTE && lex->type <= DOUBLE_QUOTES))
	if (lex->str)
		free(lex->str);
	free(lex);
	return ;
}

t_list	*clear_lexer_lst(t_list **lst, t_command_list *commands)
{
	if (commands)
		ft_lstclear(lst, lexer_content_deleter);
	else
		ft_lstclear(lst, lexer_content_free_all);
	return (NULL);
}