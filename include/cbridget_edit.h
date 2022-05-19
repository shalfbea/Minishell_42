/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/19 17:59:18 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBRIDGET_EDIT_H
# define CBRIDGET_EDIT_H

//Put your own things here, to protect minishell_h

typedef struct s_command_list {
//	char	build_in_flag;//????
	char	**redirects;//vector for all redirects. last pointer must be NULL;
	char	*redirect_flags;//flags for each redirect
	char	**argv;//first pointer is the absolut path to the command. command arguments. last pointer must be NULL;
	struct s_command_list	*next_command;//if there are no more commands, set to NULL. This is pipeline.
}	t_command_list;//linked list for commands.

# define LOGICAL_ALWAYS 0
# define LOGICAL_AND 1
# define LOGICAL_OR 2
# define BUFFER_SIZE 10

/*
typedef struct s_logical_groups {
	t_command_list			*first_command;//poiter to the first command to execute
	char					logical_flag;
	struct s_logical_groups	*next_group;
}	t_logical_groups;
*/

typedef struct s_minishell_environment {
	char	**envp;//minishell environment. it could be a list but хз
	int		ex_code;//this is the exit code of the last command.
	int		number_of_commands;//number of commands to execute
	pid_t	*pids; //[num of commands]
	char	*builtin_names[7];
	int		(*builtin_functions[7])(char ***);
	//t_logical_groups	*first_group;
}	t_minishell_environment;

typedef struct s_fds {
	int	infile;
	int	outfile;
	char	hd_flag;
	int	r_code;
	pid_t	pid_com;
	struct s_fds	*next_fd;
}	t_fds;

typedef struct s_exec_env {
	int	num_com;
	int	**_pipes;
	t_fds	*first_fd;
}	t_exec_env;

int	executor(t_minishell_environment *min_environment);
int	ft_init(t_logical_groups *group, t_exec_env *in_exec);
int	open_pipes(t_logical_groups *group, t_exec_env *in_exec);
int	alloc_pipes(int ***pipes, int num);
int	ft_free(t_logical_groups *group, t_exec_env *in_exec);
void	free_group(t_command_list *cmd);
void	free_vector(char **vct);
int	alloc_lsts(t_exec_env *in_exec, int num);
int	create_lst(t_fds **lst);
void	free_lsts(t_fds *lst);
int	open_files(t_command_list *commands, t_fds *fds);

int	run_commands(t_minishell_environment *min_environment, t_logical_groups *group, t_exec_env *in_exec);
void	ft_exec(t_minishell_environment *min_environment, t_command_list *cmd, t_exec_env *in_exec, int i);
void	create_pipeline(int	**pipes, int com, int length);
void	swap_filedescriptors(t_exec_env *in_exec, int com);

void	close_pipes(t_exec_env *in_exec, int num);
int	ft_wait(t_exec_env *in_exec);
int	ft_kill(t_exec_env *in_exec);
void	save_ex_code(t_minishell_environment *min_environment, t_exec_env *in_exec);

int	working_with_redirects(t_command_list *cmd, t_exec_env *in_exec, int num);
int	check_files(t_command_list *cmd, t_fds *tmp_fd, int num);
int	put_error(char *name, char flag);

int	heredoc(t_logical_groups *group, t_exec_env *in_exec);
int	write_heredoc(int num, char *delim);
int	hd_close(char *str, char *file_n, int fd);
int	create_file(int num, char **file_n);
char	*create_name(int num);
void	put_warning(int line, char *delim);
int	delete_heredoc(t_command_list *cmd);

char	*get_next_line(int fd);
char	*create_result(unsigned int *j, int *error, int *tmp_fd, char *letter);
char	*some_more_functions(unsigned int i, unsigned int size,
							char *result, int error);
char	*clear_end(char *result);
void	end_logic(char **result, int error, int i);
char	*my_realloc(char *result, unsigned int *size, int mod);
char	*my_realloc_two(char *result, unsigned int *size);

int	check_cmd(char **cmd, char **envp);
int	selection_path(char **cmd, char **p_path);
char	*create_new_path(char *cmd, char **p_path);
char	*search_path(char **env);


void	init_builtins(t_minishell_environment *env);
int	check_builtin(char **builtin_names, char *name);
int	run_builtin(t_minishell_environment *min_environment, t_command_list *cmd, t_exec_env *in_exec);
int	ft_echo(char ***data);
int	ft_cd(char ***data);
int	ft_pwd(char ***data);
int	ft_export(char ***data);
int	ft_unset(char ***data);
int	ft_env(char ***data);
int	ft_exit(char ***data);

#endif
