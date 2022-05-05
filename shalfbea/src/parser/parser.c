/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:42:44 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/05 19:44:06 by shalfbea         ###   ########.fr       */
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

static void	command_append(t_command_list **lst, t_command_list **cur)
{
	if (*lst == NULL)
	{
		*cur = new_command();
		*lst = *cur;
	}
	else
	{
		(*cur)->next_command = new_command();
		*cur = (*cur)->next_command;
	}
}

void	nodelete(void *element)
{
	(void) element;
	return ;
}

char	**argv_former(t_list	**argv)
{
	char	**res;
	int		words;
	t_list	*tmp;
	int		i;

	words = ft_lstsize(*argv);
	res = (char **) malloc(sizeof(char *) * (words + 1));
	tmp = *argv;
	i = 0;
	while (i < words)
	{
		res[i] = (char *) tmp->content;
		tmp = tmp->next;
		++i;
	}
	res[i] = NULL;
	ft_lstclear(argv, &nodelete);
	return (res);
}

t_command_list	*parser(t_list	*args)
{
	t_command_list	*res;
	t_command_list	*cur;
	t_lexer			*arg;
	t_list			*argv;
	int				mode;

	if (!args)
		return (NULL);
	res = NULL;
	cur = NULL;
	argv = NULL;
	mode = 0;
	command_append(&res, &cur);
	while (args)
	{
		arg = (t_lexer *) args->content;
		if (arg->type < 3) //EDIT LATER
		{
			if (mode == 0)
				ft_lstadd_back(&argv, ft_lstnew((void *)arg->str));
			if (mode == REDIR_OUT)
			{
				cur->outfile = arg->str;
				mode = 0;
			}
			if (mode == REDIR_IN)
			{
				cur->infile = arg->str;
				mode = 0;
			}
		}
		else if (arg->type == REDIR_OUT)
		{
			cur->redirect_flag_outfile = 0;
			mode = REDIR_OUT;
		}
		else if (arg->type == REDIR_IN)
		{
			cur->redirect_flag_infile = 0;
			mode = REDIR_IN;
		}
		else if (arg->type == REDIR_APPEND)
		{
			cur->redirect_flag_outfile = 1;
			mode = REDIR_OUT;
		}
		else if (arg->type == REDIR_INSOURCE)
		{
			cur->redirect_flag_infile = 1;
			mode = REDIR_IN;
		}
		else if (arg->type == PIPE)
		{
			cur->argv = argv_former(&argv);
			command_append(&res, &cur);
			mode = 0;
		}
		args=args->next;
	}
	cur->argv = argv_former(&argv);
	return (res);
}
