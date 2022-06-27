/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:29:33 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/27 18:40:57 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	int	i;

	if (sig != SIGINT)
		return ;
	g_ms_env.ex_code = 1;
	if (g_ms_env.pids) //Kill pids here
	{
		i = -1;
		while (g_ms_env.pids[++i])
			kill(g_ms_env.pids[i], SIGTERM);
		printf("\n");
	}
	else if (g_ms_env.prompt_mode)
	{
		return ;
		/*
    	rl_on_new_line();
    	rl_redisplay();
    	ft_putstr_fd("  \n", STDERR_FILENO);
    	rl_replace_line("", 0);
    	rl_on_new_line();
    	rl_redisplay();
		*/
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
	signal(SIGINT, sigint_handler);
}
