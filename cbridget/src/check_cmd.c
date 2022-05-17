/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student-21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:35:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/17 21:15:22 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char **cmd, char **envp)
{
	char	**p_path;

	if (!strncmp(*cmd, "./", 2) || !strncmp(*cmd, "../", 3) || (*cmd)[0] == '/')
	{
		if (!access(*cmd, X_OK | F_OK))
			return (0);
		else
			return (put_error(*cmd, 1));
	}
	p_path = ft_split(search_path(envp), ':');
	if (selection_path(cmd, p_path))
	{
		free_vector(p_path);
		return (1);
	}
	free_vector(p_path);
	return (0);
}

int	selection_path(char **cmd, char **p_path)
{
	char	*tmp;

	if (!p_path)
		return (1);
	while (*p_path)
	{
		tmp = create_new_path(*cmd, p_path);
		if (!tmp)
			return (1);
		if (!access(tmp, F_OK | X_OK))
		{
			free(*cmd);
			*cmd = tmp;
			return (0);
		}
		free(tmp);
		p_path++;
	}
	put_error(*cmd, 0);
	return (1);
}

char	*create_new_path(char *cmd, char **p_path)
{
	char	*tmp;
	int		length;

	length = ft_strlen(cmd);
	length += ft_strlen(*p_path);
	tmp = (char *)malloc(sizeof(char) * (length + 2));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, *p_path, ft_strlen(*p_path) + 1);
	ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
	ft_strlcat(tmp, cmd, length + 2);
	return (tmp);
}

char	*search_path(char **envp)
{
	int		i;
	char	*src;

	i = 0;
	src = "PATH";
	while (envp)
	{
		while ((*envp)[i] == src[i])
		{
			if (i == 3)
				return (&(*envp)[i + 2]);
			i++;
		}
		i = 0;
		envp++;
	}
	return ((void *)0);
}
