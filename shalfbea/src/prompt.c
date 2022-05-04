/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 18:01:23 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	error_msg(int mode)
{
	if (mode == QUOTES)
		printf("Error while parsing: quotes unmatched.");
	if (mode == P_OPEN)
		printf("Error while parsing: \'(\' parentheses unclosed");
	if (mode == P_CLOSE)
		printf("Error while parsing: \')\' parentheses unclosed");
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

char	parentheses_checker(t_list	*args)
{
	int		opened;
	char	cur;

	opened = 0;
	while (args)
	{
		cur = ((t_lexer *) args->content)->type;
		if (cur == P_OPEN)
			opened++;
		else if (cur == P_CLOSE)
		{
			if (opened > 0)
				opened--;
			else
				return (error_msg(P_CLOSE));
		}
		args = args->next;
	}
	if (opened > 0)
		return (error_msg(P_OPEN));
	return (0);
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
	if (S_DEBUG)
		ft_lstiter(args, iter_printer);
	parentheses_checker(args);
	printf("\n");
	if (str)
		free(str);
	clear_lexer_lst(&(args));
	return (0);
}
