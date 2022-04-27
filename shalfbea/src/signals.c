/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:29:33 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/27 17:42:35 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	signal_handler(int sig, siginfo_t *info, void *smth)
{
	(void) info;
	(void) smth;
	(void) sig;
	//if (sig == SIGTERM && global_struct.process != 0)
}
*/
/*
void	set_sig_control(void)
{
	t_sigacton	sigs;
	sigset_t	set;

	ft_memset(&sigs, 0, sizeof(sigs));
	sigs.sa_sigaction = signal_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sigs.sa_mask = set;
	sigaction(SIGUSR1, &sigs, 0);
	sigaction(SIGUSR2, &sigs, 0);
}
*/
