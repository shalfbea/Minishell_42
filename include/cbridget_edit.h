/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/06/28 17:08:13 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBRIDGET_EDIT_H
# define CBRIDGET_EDIT_H

# define BUFFER_SIZE 1
# define MAX_PIPES 2

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
# define ERR_SIG 128

typedef struct s_command_list {
	char					**redirects;
	char					*redirect_flags;
	char					**argv;
	struct s_command_list	*next_command;
}	t_command_list;

typedef struct s_minishell_environment {
	char	**envp;
	int		ex_code;
	int		number_of_commands;
	char	prompt_mode;
	pid_t	*pids;
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
	int		new_pipes[3][2];
	t_fds	*first_fd;
}	t_exec_env;

/*
** initializing functions, creating a list and opening pipes.
*/

int		executor(t_command_list *commands);
int		ft_init(t_command_list *commands, t_exec_env *in_exec);
int		ft_free(t_command_list *commands, t_exec_env *in_exec);
void	free_commands(t_command_list *cmd);
void	free_vector(char **vct);
int		alloc_lsts(t_exec_env *in_exec, int num);
int		create_lst(t_fds **lst);
void	free_lsts(t_fds *lst);

/*
** create child processes and execute commands
*/

int		run_commands(t_command_list *commands, t_exec_env *in_exec);
int		create_process(t_command_list *commands, t_exec_env *in_exec);
void	ft_exec(t_command_list *cmd, t_exec_env *in_exec, int i, int p_flag);
void	create_pipeline(t_exec_env *in_exec, int cmd_num, int p_flag);
int		open_pipes(t_command_list *tmp_cmd, t_exec_env *in_exec, int i);
void	swap_filedescriptors(t_exec_env *in_exec, int com, int *save);
int		alloc_pids(void);
void	close_pipes(t_exec_env *in_exec, int cmd_num, int p_flag);
int		ft_wait(t_exec_env *in_exec);
int		ft_kill(t_exec_env *in_exec);
void	save_ex_code(t_exec_env *in_exec);

/*
** working_with_redirects
*/

int		working_with_redirects(t_command_list *cmd, \
		t_exec_env *in_exec, int num);
int		check_files(t_command_list *cmd, t_fds *tmp_fd, int num);
int		open_input_files(t_command_list *cmd, t_fds *tmp_fd, int j, int num);
int		open_output_files(t_command_list *cmd, t_fds *tmp_fd, int j);
int		put_error(char *name, char flag);
int		put_error_02(char *name, char flag, char *str, int length);

/*
** these functions are for heredoc
*/

int		heredoc(t_command_list *commands, t_exec_env *in_exec);
int		heredoc_check_pipeline(t_command_list *tmp_cmd, t_fds *tmp_fd, int num);
int		fr_heredoc(t_command_list *tmp_cmd, int num, int j);
int		write_heredoc(int num, char *delim);
int		working_with_line(char *str, char *delim, int line);
int		hd_close(char *str, char *file_n, int fd);
int		create_file(int num, char **file_n);
char	*create_name(int num);
void	put_warning(int line, char *delim);
void	put_newline(char *str);
int		delete_heredoc(t_command_list *cmd);

/*
** gnl
*/

char	*get_next_line(int fd);
char	*create_result(unsigned int *j, int *error, int *tmp_fd, char *letter);
char	*some_more_functions(unsigned int i, unsigned int size,
			char *result, int error);
char	*clear_end(char *result);
void	end_logic(char **result, int error, int i);
char	*my_realloc(char *result, unsigned int *size, int mod);
char	*my_realloc_two(char *result, unsigned int *size);

/*
** search and check command
*/

int		check_cmd(char **cmd);
int		selection_path(char **cmd, char **p_path);
char	*create_new_path(char *cmd, char **p_path);
char	*search_path(void);

/*
** these functions are for builtins.
*/

void	init_builtins(void);
int		check_builtin(char *name);
int		run_builtin(t_command_list *cmd, t_exec_env *in_exec, int num);
int		run_builtin_02(t_command_list *cmd, t_exec_env *in_exec, \
		int num, int *save);
int		run_builtin_03(t_command_list *cmd, t_exec_env *in_exec, \
		int num, int *save);
void	retrieve_filedescriptors(t_exec_env *in_exec, int num, int *save);

int		print_sort_env(void);
int		print_sort_env_02(int j);
int		find_value(int i);
int		find_name(char *name);
int		check_name(char *name, char flag);
int		check_name_02(char *name, char flag, int i);
void	add_var_evp(char *name, int flag);
char	*add_var_evp_02(char *name, int flag, int length);
int		add_new_name(char *name, int length);
void	add_new_name_02(char *name, char **tmp_env, int i, int j);
void	change_name(char *name, char *tmp_name, int i);
char	*get_name(int i);
void	del_var_evp(char *variable);
int		del_var_evp_02(char **tmp_env, char *variable);
int		arg_is_number(char *str);
long	new_atoi(const char *str);
int		my_strncmp(char *s1, char *s2, size_t n);
void	skipp_n(char *str);
char	*delete_pluse(char *name);
void	add_value(char *name, int i);
void	add_value_02(char *name, int i, char *res);
int		echo_n(char flag);

int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_pwd(char **argv);
int		ft_export(char **argv);
int		ft_unset(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv);

#endif
