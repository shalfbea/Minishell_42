/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 21:11:48 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	error_msg(int mode)
{
	g_ms_env.ex_code = 2;
	if (mode == QUOTES)
		ft_putendl_fd("minishell: syntax error - quotes unmatched.",
			STDERR_FILENO);
	if (mode == P_OPEN)
		ft_putendl_fd("minishell: syntax error near unexpected token `(\'",
			STDERR_FILENO);
	if (mode == P_CLOSE)
		ft_putendl_fd("minishell: syntax error near unexpected token `)\'",
			STDERR_FILENO);
	return (1);
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
t_list	*prompt(char *input)
{
	t_list				*args;

	args = NULL;
	if (!input)
		input = readline("MiniShell: ");
	else
		input = ft_strdup(input);
	if (!input)
	{
		ft_putstr_fd("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMiniShell: exit\n", STDERR_FILENO);
		input = ft_strdup("exit");
	}
	add_history(input);
	args = lexer(input);
	if (S_DEBUG)
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

t_command_list	*get_command(t_list	*args_raw)
{
	t_command_list	*commands;
	t_list			*args;

	args = ft_lstmap(args_raw, lex_dup, &lexer_content_free_all);
	if (lst_env_check(args))
		return ((t_command_list *)clear_lexer_lst(&args));
	if (S_DEBUG)
		debug_lexer_printer("Lexer $ check", args);
	token_gluer(&args);
	if (S_DEBUG)
		debug_lexer_printer("Lexer gluing results", args);
	if (parentheses_checker(args))
	{
		clear_lexer_lst(&args);
		return (NULL);
	}
	wildcards_inserter(&args);
	if (S_DEBUG)
		debug_lexer_printer("Lexer wildcards results", args);
	commands = parser(args);
	if (S_DEBUG && commands)
		debug_command_list_printer(commands);
	clear_lexer_lst(&args);
	return (commands);
}
