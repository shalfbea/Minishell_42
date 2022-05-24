/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/24 19:26:01 by shalfbea         ###   ########.fr       */
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

t_command_list	*get_command(t_list	*args, char debug)
{
	t_command_list	*commands;

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
	// ПРОВЕРКА ПРАВИЛЬНОГО ПОРЯДКА ТОКЕНОВ
	commands = parser(args);
	if (debug && commands)
		debug_command_list_printer(commands);
	clear_lexer_lst(&(args), commands);
	return (commands);
}
