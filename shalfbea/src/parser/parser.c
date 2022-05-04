/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:42:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 20:00:39 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_cleaner(char	**argv)
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

void	clear_command(t_command_list *elem)
{
	if (elem->infile)
		free(elem->infile);
	if (elem->outfile)
		free(elem->outfile);
	argv_cleaner(elem->argv);
}

t_command_list	*clear_command_lst(t_command_list **lst)
{
	t_command_list	*cur_elem;
	t_command_list	*next_elem;
	char	check;

	check = 1;
	if (*lst == NULL)
		return (NULL);
	cur_elem = *lst;
	next_elem = *lst;
	while (check)
	{
		if (cur_elem->next_command)
			next_elem = cur_elem->next_command;
		else
			check = 0;
		clear_command(cur_elem);
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
	return (NULL);
}

t_command_list	*new_command(void)
{
	t_command_list	*list;

	list = malloc(sizeof(t_command_list));
	if (!list)
		return (NULL);
	list->build_in_flag = 0;
	list->redirect_flag_infile = -1; //Check shit
	list->infile = NULL;
	list->redirect_flag_outfile = -1; //Check shit
	list->outfile = NULL;
	list->argv = NULL;
	list->next_command = NULL;
	return (list);
}

t_command_list	*parser(t_list	*args)
{
	t_command_list	*res;
	t_command_list	*cur;

	if (!args)
		return (NULL);
	res = NULL;
	cur = NULL;
	return (NULL);
}
