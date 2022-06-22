/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:46:14 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 15:59:44 by shalfbea         ###   ########.fr       */
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
	if (msg)
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

void	debug_groups_printer(t_list	*group_lst)
{
	t_group	*cur;
	uint	group_num;

	group_num = 0;
	while (group_lst)
	{
		cur = (t_group *) group_lst->content;
		if (cur->args)
		{
			printf("-> Group %d:\n", group_num++);
			debug_lexer_printer(NULL, cur->args);
		}
		else
		{
			char	*s;
			s = NULL;
			if (cur->status == IF_AND)
				s = ft_strdup("&&");
			if (cur->status == IF_OR)
				s = ft_strdup("||");
			if (s)
			printf("operator: %s\n", s);
			else
				printf("operator: %c : %d\n", cur->status, cur->status);
			if (s)
				free(s);
		}
		group_lst = group_lst->next;
	}
}
