/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:06:00 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/22 18:40:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - s2[i]);
}

/*
** Gets name of envp (smth that goes before '=' sym).
** Unsafe function, it doesn't check if pos is > than
** envp size.
*/
char	*get_env_name(uint pos)
{
	char	*str;
	uint		i;

	str = g_ms_env.envp[pos];
	i = 0;
	while (str[i] != '=' && str[i])
		++i;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}

/*
** Gets content of envp (smth that goes after '=' sym).
** Unsafe function, it doesn't check if pos is > than
** envp size.
*/
char	*get_env_content(uint pos)
{
	char	*str;
	uint		i;

	str = g_ms_env.envp[pos];
	i = 0;
	while (str[i] != '=' && str[i])
		++i;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, i + 1, INT32_MAX));
}

char	*ft_getenv(char	*to_find)
{
	uint	i;
	char	*env_name;

	if (!to_find || !g_ms_env.envp)
		return (NULL);
	i = 0;
	while(g_ms_env.envp[i])
	{
		env_name = get_env_name(i);
		if (!ft_strcmp(to_find, env_name))
			return (get_env_content(i));
		++i;
	}
	return (NULL);
}
