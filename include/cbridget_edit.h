/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/30 19:14:32 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBRIDGET_EDIT_H
# define CBRIDGET_EDIT_H

//Put your own things here, to protect minishell_h

typedef struct s_command_list {
	char	**redirects;//vector for all redirects. last pointer must be NULL;
	char	*redirect_flags;//flags for each redirect ???flags for each redirect. 0 means: redirect >, 1 means: redirect >>, 2 means: redirect <, 3 means: redirect <<
	char	**argv;//first pointer is the absolut path to the command. command arguments. last pointer must be NULL;
	struct s_command_list	*next_command;//if there are no more commands, set to NULL. This is pipeline.
}	t_command_list;//linked list for commands.

# define LOGICAL_ALWAYS 0
# define LOGICAL_AND 1
# define LOGICAL_OR 2
# define BUFFER_SIZE 1

# define SHELL_CLOSE -55
# define NUM_BULTINS 7
# define NO_FILE -55
# define NO_VALUE 5
# define EXEC_ERROR 242

# define ERR_FEW_ARG 3
# define ERR_MANY_ARG 5
# define ERR_EXPORT 13
# define ERR_UNSET 15
# define ERR_EXIT 17
# define ERR_CD 7

# define ERR_NOCMD 127
# define ERR_SIG 130

typedef struct s_minishell_environment {
	char	**envp;//minishell environment. it could be a list but хз
	int		ex_code;//this is the exit code of the last command.
	int		number_of_commands;//number of commands to execute
	char	prompt_mode;
	pid_t	*pids; //[num of commands]
	char	*builtin_names[7];
	int		(*builtin_functions[7])(char **);
}	t_minishell_environment;

typedef struct s_fds {
	int				infile;
	int				outfile;
	int				r_code;
	char			hd_flag;
	struct s_fds	*next_fd;
}	t_fds;

typedef struct s_exec_env {
	int		**_pipes;
	t_fds	*first_fd;
}	t_exec_env;

int	executor(t_command_list *commands);
int	ft_init(t_command_list *commands, t_exec_env *in_exec);
int	open_pipes(t_command_list *commands, t_exec_env *in_exec);
int	alloc_pipes(int ***pipes, int num);
int		ft_free(t_command_list *commands, t_exec_env *in_exec);
void	free_commands(t_command_list *cmd);
void	free_vector(char **vct);
int	alloc_lsts(t_exec_env *in_exec, int num);
int	create_lst(t_fds **lst);
void	free_lsts(t_fds *lst);
int	open_files(t_command_list *commands, t_fds *fds);

int	run_commands(t_command_list *commands, t_exec_env *in_exec);
void	ft_exec(t_command_list *cmd, t_exec_env *in_exec, int i);
void	create_pipeline(int	**pipes, int com, int length);
void	swap_filedescriptors(t_exec_env *in_exec, int com, int *save);
int		alloc_pids(void);

void	close_pipes(t_exec_env *in_exec, int num);
int	ft_wait(t_exec_env *in_exec);
int	ft_kill(t_exec_env *in_exec);
void	save_ex_code(t_exec_env *in_exec);

int	working_with_redirects(t_command_list *cmd, t_exec_env *in_exec, int num);
int	check_files(t_command_list *cmd, t_fds *tmp_fd, int num);
int	put_error(char *name, char flag);

int	heredoc(t_command_list *commands, t_exec_env *in_exec);
int	write_heredoc(int num, char *delim);
int	hd_close(char *str, char *file_n, int fd);
int	create_file(int num, char **file_n);
char	*create_name(int num);
void	put_warning(int line, char *delim);
void	put_newline(char *str);
int	delete_heredoc(t_command_list *cmd);

char	*get_next_line(int fd);
char	*create_result(unsigned int *j, int *error, int *tmp_fd, char *letter);
char	*some_more_functions(unsigned int i, unsigned int size,
							char *result, int error);
char	*clear_end(char *result);
void	end_logic(char **result, int error, int i);
char	*my_realloc(char *result, unsigned int *size, int mod);
char	*my_realloc_two(char *result, unsigned int *size);

int	check_cmd(char **cmd);
int	selection_path(char **cmd, char **p_path);
char	*create_new_path(char *cmd, char **p_path);
char	*search_path(void);


void	init_builtins(void);
int	check_builtin(char *name);
int	run_builtin(t_command_list *cmd, t_exec_env *in_exec, int num);
void	retrieve_filedescriptors(t_exec_env *in_exec, int num, int *save);

int	print_sort_env(void);
int	find_value(int i);
int	find_name(char *name);
int	check_name(char *name, char flag);
void	add_var_evp(char *name, int flag);
int	add_new_name(char *name, int length);
char	*get_name(int i);
void	del_var_evp(char *variable);
int	arg_is_number(char *str);
char	*delete_pluse(char *name);
void	add_value(char *name, int i);

int	ft_echo(char **argv);
int	ft_cd(char **argv);
int	ft_pwd(char **argv);
int	ft_export(char **argv);
int	ft_unset(char **argv);
int	ft_env(char **argv);
int	ft_exit(char **argv);

#endif
