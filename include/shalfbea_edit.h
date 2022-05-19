/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shalfbea_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:59:03 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/19 20:40:57 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHALFBEA_EDIT_H
# define SHALFBEA_EDIT_H

//I'l put my things here

# define S_DEBUG 1

//U can change numbers, but some are needed to go
// together and be exact in same order (at least start and end):
//GROUP 1
# define NO_QUOTE 0
# define QUOTES 1
# define DOUBLE_QUOTES 2
//END OF GROUP 1
//GROUP 2
# define REDIR_OUT 3
# define REDIR_IN 4
# define REDIR_APPEND 5
# define REDIR_INSOURCE 6
//END OF GROUP 2
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

typedef struct s_parser_data
{
	t_command_list	*res;
	t_command_list	*cur;
	t_lexer			*arg;
	t_list			*args;
	t_list			*argv;
	t_list			*redirects;
	t_list			*redirect_flags;
	int				mode;
}	t_parser_data;

t_command_list	*prompt(char	*input, char debug);

char					error_msg(int mode);

//lexer_wraps_lst.c
void	add_to_lexer(t_list **lst, char *str, char type, char add_to_prev);
t_list	*lst_new_lex(char	*str, char type, char add_to_prev);

//lexer_free.c
t_list	*clear_lexer_lst(t_list **lst, t_command_list *commands);

//token_gluer.c
void	token_gluer(t_list **args);

//signals.c
void	set_sig_control(void);

//lexer.c
t_list	*lexer(char *str);

//lexer_specials
char	quotes_breaker(t_splitter_data *data);
char	special_characters(char	*c);
char	special_handler(t_splitter_data *data, char specials);

//lexer.c
t_command_list		*parser(t_list *args);
void				command_append(t_command_list **lst, t_command_list **cur);
t_command_list		*clear_command_lst(t_command_list **lst);

//lexer/env_check.c
char lst_env_check(t_list	*args);

//arrays.c
void	string_array_cleaner(char	**array);
char	**string_array_former(t_list	**array);
char	*char_array_former(t_list **array);
//void	char_free(void *element);
void	no_delete(void *element);

//logical_groups.c
//t_logical_groups	*form_group(t_command_list *commands);
//t_logical_groups	*clear_groups(t_logical_groups **lst);

//ms_env.c (Minishell enviroment)
//t_minishell_environment	*ms_env_cleaner(t_minishell_environment *env);
//t_minishell_environment	*ms_env_former(t_logical_groups *groups, char **envp);

//debug
void	debug_command_list_printer(t_command_list *commands);
void	debug_lexer_printer(char *msg, t_list	*args);
char	check_if_glue_needed(t_list *args); // DELETE AFTER PROD FROM HERE AND MAKE IT STATIC
//void debug_redirects_printer(char *array);

//builtins_checker.c
//
//void	builtin_checker(t_logical_groups	*groups);
#endif
