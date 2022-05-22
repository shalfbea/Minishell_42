/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:29:33 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/22 19:56:56 by shalfbea         ###   ########.fr       */
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
	if (sig == SIGINT && !g_ms_env.pids)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		printf("Minishell :");
		//rl_replace_line("", 0);
		rl_redisplay();
	}
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
