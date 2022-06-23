/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:39:57 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 15:17:48 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_list	*command_get_wrapper(void *group_data)
{
	t_group			*group;
	t_command_list	*res;

	group = (t_group *) group_data;
	res = NULL;
	if (!group)
		return (res);
	if (group->args)
		res = get_command(group->args);
	return (res);
}

static void	refresh_number_of_commands(t_command_list *lst)
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

void	execute_current(t_stack **stack, int *executor_result, t_group *cur)
{
	t_command_list	*command;
	t_group			*group_2;

	group_2 = stack_delete(stack);
	command = command_get_wrapper(stack_delete(stack));
	if (command)
	{
		refresh_number_of_commands(command);
		*executor_result = executor(command);
	}
	command = command_get_wrapper(group_2);
	if (command)
	{
		refresh_number_of_commands(command);
		if ((g_ms_env.ex_code == 0 && cur->status == IF_AND)
			|| (g_ms_env.ex_code && cur->status == IF_OR))
			*executor_result = executor(command);
	}
}

int	groups_execution(t_list *groups, t_stack *stack, int executor_result)
{
	t_group			*cur;

	while (groups)
	{
		cur = (t_group *) groups->content;
		if (cur->status == STATUS_UNDONE)
			stack = stack_push(stack, (void *) cur);
		else if (cur->status == IF_OR || cur->status == IF_AND)
			execute_current(&stack, &executor_result, cur);
		groups = groups->next;
	}
	return (executor_result);
}

int	groups_executor(t_list *groups)
{
	t_command_list	*command;

	if (!(groups->next))
	{
		command = get_command(((t_group *) groups->content)->args);
		if (command)
			return (executor(command));
		else
			return (0);
	}
	return (groups_execution(groups, NULL, 0));
}
