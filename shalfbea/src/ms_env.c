/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/22 16:44:59 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//g_ms_env.builtin_functions
	//g_ms_env.builtin_names
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

/*
t_minishell_environment *ms_env_former(t_logical_groups *groups, char **envp)
{
	t_minishell_environment	*env;

	env = (t_minishell_environment *) malloc(sizeof(t_minishell_environment));
	if (!env)
		return (NULL);
	env->envp = envp;
	env->ex_code = 0;
	env->first_group = groups;
	return (env);
}

t_minishell_environment	*ms_env_cleaner(t_minishell_environment *env)
{
	if (!env)
		return (NULL);
	//string_array_cleaner(env->envp);
	clear_groups(&(env->first_group));
	free(env);
	return (NULL);
}
*/
