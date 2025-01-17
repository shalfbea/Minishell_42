/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:27:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/28 15:41:17 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline.h>
# include <history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

# include "libft.h"
# include "cbridget_edit.h"
# include "shalfbea_edit.h"

typedef struct sigaction		t_sigacton;

extern t_minishell_environment	g_ms_env;

#endif
