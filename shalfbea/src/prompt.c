/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:56:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/27 17:38:28 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*splitter(char *str)
{
	t_list			*res;
	size_t			end;
	unsigned char	is_word;
	size_t			i;
	size_t			begin;

	end = 0;
	i = -1;
	res = NULL;
	while (str[++i])
	{
		if (!ft_isspace(str[i]) && (!is_word))
		{
			begin = i;
			is_word = 1;
		}
		if (ft_isspace(str[i]) && is_word)
		{
			is_word = 0;
			ft_lstadd_back(&res, ft_lstnew((void *) ft_substr(str, begin, end + 1)));
		}
		if (is_word)
			end = i;
	}
	if (is_word)
		ft_lstadd_back(&res, ft_lstnew((void *) ft_substr(str, begin, end + 1)));
	return (res);
}

void iter_printer(void *cur)
{
	printf("%s;", (char *) cur);
}

int	prompt(void)
{
	char	*str;
	t_list	*args;

	str = NULL;
	str = readline("MiniShell: ");
	if (!str)
		exit(0); // затычка
	args = splitter(str);
	ft_lstiter(args, iter_printer);
	printf("\n");
	if (str)
		free(str);
	return (0);
}
