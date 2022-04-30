/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/30 17:41:26 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	error_msg(int mode)
{
	if (mode == QUOTES)
		printf("Error while parsing: quotes unmatched.");
	return (1);
}


void	iter_printer(void *cur)
{
	char	*types[] = {"word", "in quotes", "in double quotes", "redir out >", "redir in <", "redir append >>", "redir insource <<", "pipe |", "if_and &&", "if_or ||", "( parenthese open",") parenthese close" };

	printf("%s;type: %s; %d flag to be added\n",
	 		((t_lexer *) cur)->str,
			 types[(int) ((t_lexer *) cur)->type],
			((t_lexer *) cur)->to_prev);

}

int	prompt(void)
{
	char	*str;
	t_list	*args;

	str = NULL;
	//str = "(lol)";
	str = readline("MiniShell: ");
	if (!str)
		exit(0); // затычка
	args = lexer(str);
	ft_lstiter(args, iter_printer);
	printf("\n");
	if (str)
		free(str);
	clear_lexer_lst(&(args));
	return (0);
}
