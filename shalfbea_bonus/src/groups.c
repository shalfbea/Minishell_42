/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:18:22 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/22 18:10:28 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_group	*group_new(t_list	*lst, char status)
{
	t_group	*res;

	res = (t_group *) malloc(sizeof(t_group));
	if (!res)
		return (NULL);
	res->args = lst;
	res->status = STATUS_UNDONE;
	if (!lst)
		res->status = status;
	return (res);
}

void	group_free(void *group_src)
{
	t_group	*group;

	group = (t_group *) group_src;
	if (!group)
		//return (NULL);
		return ;
	if (group->args)
		clear_lexer_lst(&(group->args));
	free(group);
	//return (NULL);
}

t_command_list *command_get_wrapper(void * group_data, int *last_code)
{
	t_group			*group;
	t_command_list 	*res;

	group = (t_group *) group_data;
	res = NULL;
	if (!group)
		return (res);
	if (group->args)
		res = get_command(group->args, 0);
	else
		*last_code = group->status;
	return (res);
}

void	refresh_number_of_commands(t_command_list *lst)
{
	int	counter;

	if (!lst)
		return ;
	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst->next_command;
	}
	g_ms_env.number_of_commands = counter;
}

int groups_executor(t_list *groups)
{
	t_stack			*stack;
	t_group			*cur;
	t_command_list	*command_a;
	t_command_list	*command_b;
//	t_command_list	*command;
	int				last_code;
	int				executor_result;

	stack = NULL;
	last_code = 1;
	if (!(groups->next))
	{
		command_b = get_command(((t_group *) groups->content)->args, S_DEBUG);
		refresh_number_of_commands(command_b);
		executor_result = executor(command_b);
		return (executor_result);
	}
	while (groups)
	{
		cur = (t_group *) groups->content;
		if (cur->status == STATUS_UNDONE)
			stack = stack_push(stack, (void *) cur);
		else if (cur->status == IF_OR || cur->status == IF_AND)
		{
			command_b = command_get_wrapper(stack_delete(&stack), &last_code);
			command_a = command_get_wrapper(stack_delete(&stack), &last_code);
			if (command_a)
			{
				refresh_number_of_commands(command_a);
				executor_result = executor(command_a);
				last_code = g_ms_env.ex_code;
			}
			if (command_b)
			{
				refresh_number_of_commands(command_b);
				if ((last_code == 0 && cur->status == IF_AND) || (last_code && cur->status == IF_OR))
					executor_result = executor(command_b);
				last_code = g_ms_env.ex_code;
			}
		}
		groups = groups->next;
	}
	return (executor_result);
}
