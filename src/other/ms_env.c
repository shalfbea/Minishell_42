/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/27 20:22:35 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_str_input(char *str)
{
	char	**argv;

	argv = NULL;
	if (!str)
		return ;
	argv = ft_split(str, ' ');
	if (!argv)
		return ;
	ft_export(argv);
	string_array_cleaner(&argv);
}

static void	shlvl_solver(void)
{
	char	*level_char;
	int		current_level;
	char	*command;

	level_char = NULL;
	command = NULL;
	level_char = find_in_env("SHLVL", -1, 5);
	if (!level_char[0])
		ft_export_str_input("! SHLVL=1");
	else
	{
		current_level = ft_atoi(level_char);
		free(level_char);
		level_char = ft_itoa(++current_level);
		command = ft_strjoin("! SHLVL=", level_char);
		ft_export_str_input(command);
	}
	if (level_char)
		free(level_char);
	if (command)
		free(command);
}

static void	pwd_solver(void)
{
	char	*command;
	char	*path;
	char	*cur;

	cur = NULL;
	path = NULL;
	command = NULL;
	cur = find_in_env("PWD", -1, 3);
	if (!cur[0])
	{
		path = getcwd(NULL, 0);
		if (path)
		{
			command = ft_strjoin("! PWD=", path);
			ft_export_str_input(command);
		}
	}
	if (cur)
		free(cur);
	if (path)
		free(path);
	if (command)
		free(command);
}

/*
** Call this function in the beginning or program
** with envp provided my main function
** to correctly init global variable.
*/
char	ms_env_initter(char **envp)
{

	g_ms_env.ex_code = 0;
	g_ms_env.number_of_commands = 0;
	g_ms_env.pids = NULL;
	g_ms_env.envp = string_array_copy(envp, 0);
	g_ms_env.prompt_mode = 0;
	shlvl_solver();
	pwd_solver();
	init_builtins();
	if (!g_ms_env.envp)
		return (1);
	return (0);
}

/*
** Add new element to envp in ms_env global structure
** Doesn't check if the new string is correct at that time.
*/
char	envp_add_string(char *new_element)
{
	int		len;
	char	**new_envp;

	if (!new_element)
		return (0);
	len = 0;
	new_envp = string_array_copy(g_ms_env.envp, 1);
	while (new_envp[len])
		len++;
	new_envp[len++] = ft_strdup(new_element);
	new_envp[len] = NULL;
	string_array_cleaner(&(g_ms_env.envp));
	g_ms_env.envp = new_envp;
	return (0);
}
