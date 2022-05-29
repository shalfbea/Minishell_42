/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:58:55 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/29 15:33:45 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_in_env(char *str, int start_pos, int end_pos)
{
	char	*request;
	char	*env;

	request = ft_substr(str, start_pos + 1, end_pos - start_pos);
	env = ft_getenv(request);
	if (request)
		free(request);
	if (env)
		return (env);
	return (ft_strdup(""));
	/*
	env = malloc(sizeof(char) * 1);
	if (!env)
		return (NULL); //RAISE ERROR
	env[0] = '\0';
	return (env);
	*/
}

static void	str_replace_with_env(char	**str, int start_pos, int end_pos)
{
	char	*res;
	int		i;
	int		k;
	char	*env;

	if (!(*str))
		return ;
	env = find_in_env(*str, start_pos, end_pos);
	res = (char *) malloc((sizeof(char)
				* ((ft_strlen(*str) + ft_strlen(env)
						+ start_pos - end_pos + 1))));
	i = 0;
	k = 0;
	while ((*str)[i] && i < start_pos)
		res[k++] = (*str)[i++];
	i = 0;
	while (env[i])
		res[k++] = env[i++];
	i = end_pos;
	while ((*str)[++i])
		res[k++] = (*str)[i];
	res[k] = '\0';
	free(*str);
	free(env);
	*str = res;
}

static char	env_checker(char	**str)
{
	int	i;
	int	k;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			k = i + 1;
			if (!(*str)[k])
				return (1);
			while ((*str)[k] && ft_isalnum((*str)[k]))
				++k;
			str_replace_with_env(str, i, k - 1);
			i = 0;
		}
	}
	return (0);
}

char	lst_env_check(t_list	*args)
{
	t_lexer	*cur;

	while (args)
	{
		cur = (t_lexer *) args ->content;
		if (cur->type == NO_QUOTE || cur->type == DOUBLE_QUOTES)
		{
			if (env_checker(&(cur->str)))
				return (1);
		}
		args = args->next;
	}
	return (0);
}
