/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:58:55 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/12 12:51:44 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static char	env_checker(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return ;///////We need to go deeper
		++i;
	}
}
*/
/*
char	lst_env_check(t_list	*args)
{
	t_lexer	*cur;

	cur = (t_lexer *) args;
	while(cur)
	{
		if (cur->type == NO_QUOTE || cur->type == DOUBLE_QUOTES)
			env_checker(....
	}
}
*/
