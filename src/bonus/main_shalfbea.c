/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shalfbea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:18:23 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_set_envp(void);

t_minishell_environment g_ms_env;

int logical_support(void)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int				executor_result;
	t_list			*groups;

	commands = NULL;
	int	i = 1;
	(void) i;
	//FOR DEBUGGING ONLY
	//string_array_cleaner(&g_ms_env.envp);
	//debug_set_envp();
	//
	while (i--)
	{
		g_ms_env.prompt_mode = 1;
		raw_lexer_data = prompt("e >");
		g_ms_env.prompt_mode = 0;
		groups = to_polish_notation(raw_lexer_data);
		//debug_lexer_printer("Polish notation", raw_lexer_data);
		if (S_DEBUG)
			debug_groups_printer(groups);
		//pause();
		//commands = get_command(raw_lexer_data, debug);
		//if (!commands)
		//	break ;
		//executor_result = executor(commands);
		if (groups)
			executor_result = groups_executor(groups);
		(void) executor_result;
		clear_lexer_lst(&(raw_lexer_data));
		//ft_lstclear(&groups, group_free);
		//clear_command_lst(&commands);
	}
	string_array_cleaner(&g_ms_env.envp);
	//sleep(5);
	//pause();
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_command_list	*commands;
	t_list			*raw_lexer_data;
	int				executor_result;

	(void ) argc;
	(void ) argv;
	(void ) envp;
	commands = NULL;
	if (ms_env_initter(envp))
		exit(1);
	set_sig_control();
	logical_support(); //DEBUG
	int	i = 1;
	(void) i;
	//FOR DEBUGGING ONLY
	//string_array_cleaner(&g_ms_env.envp);
	//debug_set_envp();
	//
	while (i--)
	{
		//if (debug)
		//	debug_ms_env_printer();
		g_ms_env.prompt_mode = 1;
		raw_lexer_data = prompt("cat << $PATH");
		g_ms_env.prompt_mode = 0;
		commands = get_command(raw_lexer_data);
		if (!commands)
			break ;
		executor_result = executor(commands);
		(void) executor_result;
		clear_lexer_lst(&(raw_lexer_data));
		//clear_command_lst(&commands);
	}
	string_array_cleaner(&g_ms_env.envp);
	//sleep(5);
	return (0);
}


void	debug_set_envp(void)
{
	int	params_num;

	params_num = 2;
	g_ms_env.envp = (char **) malloc(sizeof(char *) * (params_num + 1));
	g_ms_env.envp[0] = ft_strdup("USER=shalfbea");
	g_ms_env.envp[1] = ft_strdup("HOME=keklol/shalfbea");
	g_ms_env.envp[2] = NULL;
}
