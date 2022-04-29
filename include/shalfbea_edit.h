/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shalfbea_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:59:03 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/29 19:47:13 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHALFBEA_EDIT_H
# define SHALFBEA_EDIT_H

//I'l put my things here
void	builtin_exit(int num);
int		prompt(void);

//lexer_wraps_lst.c
void	add_to_lexer(t_list **lst, char *str, char type);
t_list	*clear_lexer_lst(t_list **lst);

//signals.c
void	set_sig_control(void);

# define NO_QUOTE 0
# define QUOTES 1
# define DOUBLE_QUOTES 2
# define REDIR_OUT 3
# define REDIR_IN 4
# define REDIR_APPEND 5
# define REDIR_INSOURCE 6
# define PIPE 7
# define IF_AND 8
# define IF_OR 9
# define P_OPEN 10
# define P_CLOSE 11

typedef struct s_lexer
{
	char			*str;
	char			type;
}	t_lexer;

#endif
