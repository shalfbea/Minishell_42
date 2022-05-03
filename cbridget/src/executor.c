/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/03 13:58:59 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell_environment *min_environment)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	if (ft_init(min_environment, &in_exec))
		return (1);

/*	t_fds *test;
	test = in_exec.first_fd;
	while (test)
	{
		printf("outfile=%d\n", test->outfile);
		test = test->next_fd;
	}
	ft_free(&in_exec);*/

	if (run_commands(min_environment, &in_exec))
		return (1);
	ft_free(min_environment, &in_exec, 1);
	return (0);
}
