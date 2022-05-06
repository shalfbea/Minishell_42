/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:22:45 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/06 15:46:09 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell_environment *min_environment)
{
	t_exec_env	in_exec;

	in_exec.first_fd = NULL;
	in_exec.envp_in = min_environment->envp;
	if (ft_init(min_environment->first_group, &in_exec))
		return (1);

/*	t_fds *test;
	test = in_exec.first_fd;
	while (test)
	{
		printf("outfile=%d\n", test->outfile);
		test = test->next_fd;
	}
	ft_free(&in_exec);*/

	if (run_commands(min_environment->first_group, &in_exec))
		return (1);
//	ft_free(min_environment, &in_exec);
	return (0);
}
