/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:14:59 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/28 14:08:47 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_lexer_if_file_visible(t_list **lst, char *str)
{
	if (!str)
		return ;
	if (!(*str) || *str == '.')
		return ;
	add_to_lexer(lst, ft_strdup(str), 0, 0);
}

t_list	*lst_file_sort_like_bash(t_list *lst)
{
	t_list	*i;
	t_list	*j;

	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	i = lst;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(((t_lexer *) i->content)->str, ((t_lexer *) j->content)->str) > 0)
				ft_lst_content_swap(i, j);
			j = j->next;
		}
		i = i->next;
	}
	return (lst);
}

t_list	*directory_wildcard(void)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_list			*result;

	result = NULL;
	dirp = opendir(".");
	while (dirp)
	{
		errno = 0;
		dp = readdir(dirp);
		if (dp)
			add_to_lexer_if_file_visible(&result, dp->d_name);
			//add_to_lexer(&result, ft_strdup(dp->d_name), 0, 0);
			//add_to_lexer(&result, ft_strjoin(ft_strjoin(ft_strdup(dp->d_name), "_"), ft_itoa(dp->d_seekoff)), 0, 0);
		else
		{
			if (errno == 0)
			{
				closedir(dirp);
				return (result);//NOT_FOUND;
			}
			closedir(dirp);
			return (NULL);//READ_ERROR; <========================= mmargene talks about it u need think
		}
	}
	return (result);//OPEN_ERROR;
}

char	wildcards_inserter(t_list	**args_head)
{
	t_list	*args;
	t_list	*tmp_next;

	args = *args_head;
	while (args)
	{
		if (((t_lexer *)args->content)->type == WILDCARD)
		{
			tmp_next = args->next;
			args->next = lst_file_sort_like_bash(directory_wildcard());
			while (args->next)
				args = args->next;
			args->next = tmp_next;
		}
		args = args->next;
	}
	return (0);
}
