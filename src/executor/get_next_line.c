/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:40:24 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/28 22:14:23 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	static int			tmp_fd;
	static char			letter[BUFFER_SIZE];
	static int			error;
	static unsigned int	j;

	if (fd != tmp_fd || j == BUFFER_SIZE || j == (unsigned int)error)
	{
		if (fd != tmp_fd)
			tmp_fd = fd;
		error = read(tmp_fd, letter, BUFFER_SIZE);
		j = 0;
	}
	return (create_result(&j, &error, &tmp_fd, letter));
}

char	*create_result(unsigned int *j, int *error, int *tmp_fd, char *letter)
{
	char			*result;
	unsigned int	i;
	unsigned int	size;

	i = 0;
	size = BUFFER_SIZE;
	result = my_realloc((void *)0, &size, 1);
	if (!result)
		return ((void *)0);
	while (*error && *error != -1 && (i == 0
			|| (result[i - 1] && result[i - 1] != '\n')))
	{
		if (i == size)
			result = my_realloc(result, &size, 0);
		if (!result)
			return ((void *)0);
		result[i++] = letter[(*j)++];
		if ((*j == BUFFER_SIZE || *j == (unsigned int)(*error))
			&& result[i - 1] != '\n' && result[i - 1])
		{
			*error = read(*tmp_fd, letter, BUFFER_SIZE);
			*j = 0;
		}
	}
	return (some_more_functions(i, size, result, *error));
}

char	*some_more_functions(unsigned int i, unsigned int size,
							char *result, int error)
{
	if (i == size)
		result = my_realloc(result, &size, 0);
	if (!result)
		return ((void *)0);
	end_logic(&result, error, i);
	if (result)
		result = clear_end(result);
	return (result);
}

char	*clear_end(char *result)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (result[i])
		i ++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
	{
		free(result);
		return ((void *)0);
	}
	i = 0;
	while (result[i])
	{
		tmp[i] = result[i];
		i++;
	}
	tmp[i] = '\0';
	free(result);
	return (tmp);
}

void	end_logic(char **result, int error, int i)
{
	if ((*result)[0] == -1 || error == -1)
	{
		if ((*result)[0] == -1)
			(*result)[0] = NO_FILE;
		else
		{
			free(*result);
			*result = (void *)0;
		}
	}
	else if (!error)
		(*result)[i] = '\0';
	else if ((*result)[0])
	{
		if ((*result)[i - 1] != '\n')
		{
			(*result)[i] = '\n';
			i++;
		}
		(*result)[i] = '\0';
	}
}
