/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:23:41 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/12 16:27:51 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	string_array_cleaner(env->envp);
	clear_groups(&(env->first_group));
	free(env);
	return (NULL);
}
