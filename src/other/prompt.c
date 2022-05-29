/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/29 18:58:48 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	error_msg(int mode)
{
	if (mode == QUOTES)
		//printf("minishell: syntax error - quotes unmatched.");
		ft_putendl_fd("minishell: syntax error - quotes unmatched.",
			STDERR_FILENO);
	if (mode == P_OPEN)
		//printf("minishell: syntax error near unexpected token `(\'\n");
		ft_putendl_fd("minishell: syntax error near unexpected token `(\'",
			STDERR_FILENO);
	if (mode == P_CLOSE)
		//printf("minishell: syntax error near unexpected token `)\'\n");
		ft_putendl_fd("minishell: syntax error near unexpected token `)\'",
			STDERR_FILENO);
	return (1);
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

/*
** Gives user prompt to input command and returns
** t_list* structure with a result of lexer
** Also can be called with input string, avoiding input from user,
** just to for testing purposes.
** debug defaults to 0, if called with '1' will show debug info
** in standart output.
** Exits the whole program, if nothing or 'exit' has been inputted.
** default call:
** raw_lexer_data = prompt(NULL, 1);
*/
t_list	*prompt(char *input, char debug)
{
	t_list				*args;
	t_command_list		*commands;

	args = NULL;
	commands = NULL;
	if (!input)
		input = readline("MiniShell: ");
	else
		input = ft_strdup(input);
	if (!input) //HANDLING CTRL-D HERE
	{
		ft_putstr_fd("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMiniShell: exit\n", STDERR_FILENO);
		input = ft_strdup("exit");
	}
	if (!ft_strncmp(input, "exit", 4)) //DELETE IT LATER
		exit(0); // затычка
	add_history(input);
	args = lexer(input);
	if (debug)
		debug_lexer_printer("Lexer primary results", args);
	free(input);
	return (args);
}

void	*lex_dup(void *original)
{
	t_lexer	*copy;

	copy = (t_lexer *) malloc(sizeof(t_lexer *));
	copy->str = ft_strdup(((t_lexer *) original)->str);
	copy->to_prev = ((t_lexer *) original)->to_prev;
	copy->type = ((t_lexer *) original)->type;
	return ((void *) copy);
}

t_command_list	*get_command(t_list	*args_raw, char debug)
{
	t_command_list	*commands;
	t_list			*args;

	args = ft_lstmap(args_raw, lex_dup, &no_delete);
	if (lst_env_check(args))
		return ((t_command_list *)clear_lexer_lst(&args, NULL));
	if (debug)
		debug_lexer_printer("Lexer $ check", args);
	if (check_if_glue_needed(args))
	{
		token_gluer(&args);
		if (debug)
			debug_lexer_printer("Lexer gluing results", args);
	}
	if (parentheses_checker(args))
	{
		clear_lexer_lst(&args, NULL);
		return (NULL);
	}
	wildcards_inserter(&args);
	if (debug)
		debug_lexer_printer("Lexer wildcards results", args);
	// ПРОВЕРКА ПРАВИЛЬНОГО ПОРЯДКА ТОКЕНОВ
	commands = parser(args);
	if (debug && commands)
		debug_command_list_printer(commands);
	clear_lexer_lst(&args, NULL);
	return (commands);
}
