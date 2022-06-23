/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shalfbea_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:59:03 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/23 18:38:00 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHALFBEA_EDIT_H
# define SHALFBEA_EDIT_H

# define S_DEBUG 0

# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif
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
# define WILDCARD 12

# define STATUS_UNDONE 0
# define STATUS_DONE_WELL 1
# define STATUS_DONE_BAD 2

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

typedef struct s_group
{
	t_list					*args;
	char					status;
}	t_group;

typedef t_list	t_stack;

t_list					*prompt(char	*input);
t_command_list			*get_command(t_list	*args);
char					error_msg(int mode);
void					add_to_lexer(t_list **lst, char *str,
							char type, char add_to_prev);
t_list					*lst_new_lex(char	*str, char type, char add_to_prev);
t_lexer					*lexer_dup(t_lexer *lex);
t_list					*clear_lexer_lst(t_list **lst);
void					token_gluer(t_list **args);
void					set_sig_control(void);
t_list					*lexer(char *str);
void					lexer_content_free_all(void *content);
char					quotes_breaker(t_splitter_data *data);
char					special_characters(char	*c);
char					special_handler(t_splitter_data *data, char specials);
t_command_list			*parser(t_list *args);
t_list					*ft_lstnew_from_char(char c);
t_command_list			*error_and_clean(t_parser_data *data, char *error_msg);
void					command_append(t_command_list **lst,
							t_command_list **cur);
t_command_list			*clear_command_lst(t_command_list **lst);
char					parentheses_checker(t_list	*args);
char					lst_env_check(t_list	*args);
char					*ft_getenv(char	*to_find);
char					*get_env_content(uint pos);
char					*get_env_name(uint pos);
void					string_array_cleaner(char	***array);
char					**string_array_former(t_list	**array);
char					**string_array_copy(char **array,
							uint more_size_option);
char					*char_array_former(t_list **array);
void					no_delete(void *element);
char					ms_env_initter(char **envp);
char					envp_add_string(char *new_element);
void					debug_command_list_printer(t_command_list *commands);
void					debug_lexer_printer(char *msg, t_list	*args);
void					debug_ms_env_printer(void);
void					debug_groups_printer(t_list	*group_lst);
char					wildcard_handler(t_splitter_data *data);
char					wildcards_inserter(t_list	**args);
t_list					*to_polish_notation(t_list *args);
t_stack					*stack_push(t_stack *head, void *content);
void					*stack_delete(t_stack **head);
t_group					*group_new(t_list	*lst, char status);
void					group_free(void *group);
int						groups_executor(t_list *groups);
int						real_main(char **envp, char bonus);
#endif
