/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:29:33 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/29 16:13:35 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Need to be rewritten later
*/
void	signal_handler(int sig, siginfo_t *info, void *smth)
{
	//static char	first_exit;

	(void) info;
	(void) smth;
	//(void) sig;
	if (sig == SIGINT)
	{
		printf("\nExitting!\n");
		exit(0);
	}
	//if (sig == )
}

/*
**
** Signals handler
** CTRL-C = SIGINT
** CTRL-\ = SIGQUIT
** CTRL-Z = SIGTSTP
*/
void	set_sig_control(void)
{
	t_sigacton	sigs;
	sigset_t	set;

	ft_memset(&sigs, 0, sizeof(sigs));
	sigs.sa_sigaction = signal_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGTSTP);
	sigs.sa_mask = set;
	sigaction(SIGINT, &sigs, 0);
	sigaction(SIGQUIT, &sigs, 0);
	sigaction(SIGTSTP, &sigs, 0);
}
