/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/04/30 18:26:18 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell_environment *exe_environment)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	if (ft_init(exe_environment, &in_exec))
		return (1);

	t_fds *test;
	test = in_exec.first_fd;
	while (test)
	{
		printf("outfile=%d\n", test->outfile);
		test = test->next_fd;
	}
	ft_free(&in_exec);

	return (0);
//	if (build_in && exe_environment->number_of_commands == 1)
//		executor_one();
}
