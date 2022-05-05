/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shalfbea_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:59:03 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/04 18:44:41 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHALFBEA_EDIT_H
# define SHALFBEA_EDIT_H

//I'l put my things here

# define S_DEBUG 1

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
	char			to_prev;
}	t_lexer;

typedef struct s_splitter_data
{
	t_list	*res;
	char	is_word;
	size_t	i;
	size_t	begin;
	char	*str;
	char	after_quotes;
}	t_splitter_data;

void	builtin_exit(int num);
int		prompt(void);
char	error_msg(int mode);

//lexer_wraps_lst.c
//void	add_to_lexer(t_list **lst, char *str, char type);
void	add_to_lexer(t_list **lst, char *str, char type, char add_to_prev);
t_list	*clear_lexer_lst(t_list **lst);

//signals.c
void	set_sig_control(void);

//lexer.c
t_list	*lexer(char *str);

//lexer_specials
char	quotes_breaker(t_splitter_data *data);
char	special_characters(char	*c);
char	special_handler(t_splitter_data *data, char specials);

//lexer.c
t_command_list	*parser(t_list	*args);
#endif
