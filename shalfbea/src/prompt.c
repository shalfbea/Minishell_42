/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 21:03:12 by shalfbea         ###   ########.fr       */
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

void	debug_command_list_printer(t_command_list *commands)
{
	int		i;
	char	**argv;

	i = 0;
	if (!commands)
		printf("List is empty!\n");
	while (commands)
	{
		printf("COMMAND %d: \n\n", i++);
		printf("build_in_flag : %d\n", commands->build_in_flag);
		printf("redirect_flag_infile : %d\n", commands->redirect_flag_infile);
		printf("infile : %s\n", commands->infile);
		printf("redirect_flag_outfile : %d\n", commands->redirect_flag_outfile);
		printf("outfile : %s\n", commands->outfile);
		printf("argv : ");
		if (commands->argv)
		{
			argv = commands->argv;
			while (*argv)
			{
				printf("%s", *argv);
				(*argv)++;
			}
		}
		else
			printf("NO_ARGS");
		printf("\n\n");
	}
}

int	prompt(void)
{
	char			*str;
	t_list			*args;
	t_command_list	*commands;

	str = NULL;
	args = NULL;
	commands = NULL;
	//str = "(lol)";
	str = readline("MiniShell: ");
	if (!str)
		exit(0); // затычка
	args = lexer(str);
	if (S_DEBUG)
	{
		printf("\nLexer results:\n\n");
		ft_lstiter(args, iter_printer);
		printf("\n===================\n===================\n");
	}
	parentheses_checker(args);
	if (S_DEBUG && commands)
	{
		printf("\nParser results:\n");
		debug_command_list_printer(commands);
		printf("\n===================\n===================\n");
	}
	printf("\n");
	if (str)
		free(str);
	clear_lexer_lst(&(args));
	return (0);
}
