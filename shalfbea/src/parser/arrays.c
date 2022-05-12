/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:13:16 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/12 17:57:40 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_delete(void *element)
{
	(void ) element;
	//if (element)
	//	free(element);
}

char	**string_array_former(t_list	**array)
{
	char	**res;
	int		words;
	t_list	*tmp;
	int		i;

	words = ft_lstsize(*array);
	res = (char **) malloc(sizeof(char *) * (words + 1));
	tmp = *array;
	i = 0;
	while (i < words)
	{
		res[i] = (char *) tmp->content;
		tmp = tmp->next;
		++i;
	}
	res[i] = NULL;
	ft_lstclear(array, &no_delete);
	return (res);
}

char	*char_array_former(t_list **array)
{
	int		size;
	int		i;
	char	*res;
	t_list	*tmp;

	tmp = *array;
	size = ft_lstsize(tmp);
	res = (char *) malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		res[i] = ((char *)tmp->content)[0];
		tmp = tmp->next;
	}
	res[i] = '\0';
	ft_lstclear(array, &free);
	return (res);
}

void	string_array_cleaner(char	**argv)
{
	int		i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	if (argv)
		free(argv);
	argv = NULL;
}
