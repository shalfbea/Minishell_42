/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/19 19:23:20 by shalfbea         ###   ########.fr       */
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
** t_minishell_environment structure with a result of parsing
** Also can be called with input string, avoiding input from user,
** just to for testing purposes.
** debug defaults to 0, if called with '1' will show debug info
** in standart output.
** Exits the whole program, if nothing or 'exit' has been inputted.
** default call:
** tmp = prompt(NULL, 1);
*/
t_command_list	*prompt(char *input, char debug)
{
	t_list				*args;
	t_command_list		*commands;
	char				need_free;

	args = NULL;
	commands = NULL;
	need_free = 0;
	//input = "| | ";
	if (!input)
	{
		input = readline("MiniShell: ");
		need_free = 1;
	}
	if (!input[0] || !ft_strncmp(input, "exit", 4))
		exit(0); // затычка
	add_history(input);
	args = lexer(input);
	if (debug)
		debug_lexer_printer("Lexer primary results", args);
	if (lst_env_check(args))
		return ((t_command_list	*)clear_lexer_lst(&args, NULL));
	if (debug)
		debug_lexer_printer("Lexer $ check", args);
	if (check_if_glue_needed(args))
	{
		token_gluer(&args);
		if (debug)
			debug_lexer_printer("Lexer gluing results", args);
	}
	parentheses_checker(args);
	// ПРОВЕРКА СОДЕРЖИМОГО КОВЫЧЕК :
	// ПРОВЕРКА ПРАВИЛЬНОГО ПОРЯДКА ТОКЕНОВ
	commands = parser(args);
	// ПРОВЕРКА ARGV[0] - название программы - судя по всему не нужно
	//if (S_DEBUG && commands)
	if (debug && commands)
		debug_command_list_printer(commands);
	//if (need_free)
	//	free(input);
	clear_lexer_lst(&(args), commands);
	//clear_groups(&groups);
	//pause();
	//return (ms_env_former(groups, NULL));
	return (commands);
}
