/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:46:14 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/07 17:47:07 by shalfbea         ###   ########.fr       */
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
	char	*types[] = {"word", "in quotes", "in double quotes", "redir out >", "redir in <", "redir append >>", "redir insource <<", "pipe |", "if_and &&", "if_or ||", "( parenthese open",") parenthese close", "wildcard"};

	printf("%s; Type: %s",
	 	  ((t_lexer *) cur)->str,
			types[(int) ((t_lexer *) cur)->type]
			);
	if (((t_lexer *) cur)->to_prev)
		printf("; This adds to prev.");
	printf("\n");

}

void	debug_lexer_printer(char *msg, t_list	*args)
{
	printf("\n%s:\n\n", msg);
	ft_lstiter(args, iter_printer);
	printf("\n===================\n===================\n");
}

void	debug_ms_env_printer(void)
{
	int	i;

	i = -1;
	printf("envp: \n");
	if (!g_ms_env.envp)
		printf("NULL\n");
	while(g_ms_env.envp[++i])
		printf("%s\n", g_ms_env.envp[i]);
	printf("\nExit code: %d\n", g_ms_env.ex_code);
	printf("Number of commands: %d\n", g_ms_env.number_of_commands);
	i = -1;
	if (g_ms_env.pids)
	{
		printf("pids: \n");
		while (g_ms_env.pids[++i])
		{
			printf("%d", g_ms_env.pids[i]);
			if (g_ms_env.pids[i+1])
				printf(", ");
		}
		printf("\n");
	}
	else
		printf("Pids not presented.\n");
}

void	debug_lt_printer(t_logical_tree *head, char child, int indent)
{
	int	syms;
	t_list	*args;

	syms = 0;
	if (child)
	{
		for (int i = 0; i < indent; ++i)
			printf(" ");
		printf("↓\n");
		for (int i = 0; i < indent; ++i)
			printf(" ");
	}
	while (head)
	{
		//if (head->child)
		//	debug_lt_printer(head->child, 1, indent + syms);
		args = head->args;
		if (args)
		{
			while (args->next)
			{
				printf("%s,", ((t_lexer *)args->content)->str);
				args = args->next;
			}
			printf("%s;", ((t_lexer *)args->content)->str);
		}
		head = head->next;
	}
}
