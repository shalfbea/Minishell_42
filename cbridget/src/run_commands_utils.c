/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:34:00 by cbridget          #+#    #+#             */
/*   Updated: 2022/05/20 14:36:09 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_pids(void)
{
	g_ms_env.pids = (pid_t *)malloc(sizeof(pid_t) * g_ms_env.number_of_commands);
	if (!g_ms_env.pids)
		return (1);
	return (0);
}