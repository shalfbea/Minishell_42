/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:03:07 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:04:21 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*debug_redirects_syms(char k)
{
	if (k == 0)
		return (">");
	else if (k == 1)
		return ("<");
	else if (k == 2)
		return (">>");
	else if (k == 3)
		return ("<<");
	return (NULL);
}

static void	debug_redirects_printer(char *array)
{
	int		k;

	k = 0;
	printf("redirect_flags: ");
	while (array[k])
	{
		printf("%s", debug_redirects_syms(array[k] - REDIR_OUT));
		if (array[k + 1])
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
	while (array[k])
	{
		printf("%s", array[k]);
		if (array[k + 1])
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
		debug_array_printer("redirects", commands->redirects);
		debug_redirects_printer(commands->redirect_flags);
		debug_array_printer("argv", commands->argv);
		commands = commands->next_command;
		if (commands)
			printf("======\n");
	}
	printf("\n===================\n===================\n\n");
}
