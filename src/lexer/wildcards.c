/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:14:59 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/29 19:18:00 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*directory_wildcard(void)
{
	DIR 			*dirp;
	struct dirent	*dp;
	t_list			*result;

	result = NULL;
	dirp = opendir("."); // NOT THIS DIRECTORY MAY BE
	while (dirp)
	{
 	   errno = 0;
	    if ((dp = readdir(dirp)) != NULL)
			add_to_lexer(&result, ft_strdup(dp->d_name), 0, 0);
		else
		{
	        if (errno == 0)
			{
	            closedir(dirp);
	            return (result);//NOT_FOUND;
		    }
		    closedir(dirp);
		    return NULL;//READ_ERROR; <========================= mmargene talks about it u need think
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
		t_lexer *cur = (t_lexer *)args->content;
		(void) cur;
		if (((t_lexer *)args->content)->type == WILDCARD)
		{
			tmp_next = args->next;
			args->next = directory_wildcard();
			while (args->next)
				args = args->next;
			args->next = tmp_next;
		}
		args = args->next;
	}
	return (0);
}