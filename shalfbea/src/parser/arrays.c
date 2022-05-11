/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:13:16 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/11 21:08:54 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nodelete(void *element)
{
	(void) element;
	return ;
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
	ft_lstclear(array, &nodelete);
	return (res);
}

void	string_array_cleaner(char	**argv)
{
	char	*cur;

	if (!argv)
		return ;
	cur = *argv;
	while (cur)
	{
		free(cur);
		cur++;
	}
	if (argv)
		free(argv);
	*argv = NULL;
}

//void array_printer(char **strings)
