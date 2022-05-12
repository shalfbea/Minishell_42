/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:46:14 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/12 16:30:59 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void debug_redirects_printer(char *array)
{
	char	*redirs[] = {">", "<", ">>", "<<"};
	int		k;

	k = 0;
	printf("redirect_flags: ");
	while (array[k])
	{
		printf("%s", redirs[array[k] - REDIR_OUT]);
		//printf("%c", array[k] + '0');
		if (array[k+1])
			printf(", ");
		k++;
	}
	printf("\n");
}

static void	debug_array_printer(char *name, char **array)
{
	int	k;

	k = 0;
	printf("%s: ", name);
	//if (!(*array))
	//	return ;
	while (array[k])
	{
		printf("%s", array[k]);
		if (array[k+1])
			printf(", ");
		k++;
	}
	printf("\n");
}

void	debug_command_list_printer(t_command_list *commands)
{
	int		i;

	i = 0;
	printf("\nParser results:\n");
	if (!commands)
		printf("List is empty!\n");
	while (commands)
	{
		printf("COMMAND %d: \n\n", i++);
		printf("build_in_flag : %d\n", commands->build_in_flag);
		debug_array_printer("redirects", commands->redirects);
		//printf("redirect_flags: %s\n", commands->redirect_flags);
		debug_redirects_printer(commands->redirect_flags);
		debug_array_printer("argv", commands->argv);
		commands = commands->next_command;
		if (commands)
			printf("======\n");
	}
	printf("\n===================\n===================\n\n");
}

void	iter_printer(void *cur)
{
	char	*types[] = {"word", "in quotes", "in double quotes", "redir out >", "redir in <", "redir append >>", "redir insource <<", "pipe |", "if_and &&", "if_or ||", "( parenthese open",") parenthese close" };

	printf("%s;type: %s; %d flag to be added\n",
	 		((t_lexer *) cur)->str,
			 types[(int) ((t_lexer *) cur)->type],
			((t_lexer *) cur)->to_prev);

}

void	debug_lexer_printer(char *msg, t_list	*args)
{
	printf("\n%s:\n\n", msg);
	ft_lstiter(args, iter_printer);
	printf("\n===================\n===================\n");
}
