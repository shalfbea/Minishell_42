/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/10 15:14:00 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBRIDGET_EDIT_H
# define CBRIDGET_EDIT_H

//Put your own things here, to protect minishell_h

typedef struct s_command_list {
	char	build_in_flag;//????
/*	char	*redirect_flag_infile;// 0 means: redirect >, 1 means: redirect >>.
	char	**infile;//pointer to a string with named infile, NULL means no file.
	char	*redirect_flag_outfile;// same as redirect_flag_infile but for outfile.
	char	**outfile;//same as *infile but for outfile.*///that's not right
	char	**redirects;//vector for all redirects. last pointer must be NULL;
	char	*redirect_flags;//flags for each redirect. 0 means: redirect >, 1 means: redirect >>, 2 means: redirect <, 3 means: redirect <<;
	char	**argv;//first pointer is the absolut path to the command. command arguments. last pointer must be NULL;
	struct s_command_list	*next_command;//if there are no more commands, set to NULL. This is pipeline.
}	t_command_list;//linked list for commands.

# define LOGICAL_ALWAYS 0
# define LOGICAL_AND 1
# define LOGICAL_OR 2

typedef struct s_logical_groups {
	t_command_list			*first_command;//poiter to the first command to execute
	int						number_of_commands;//number of commands to execute
	char					logical_flag;
	struct s_logical_groups	*next_group;
}	t_logical_groups;

typedef struct s_minishell_environment {
	char	**envp;//minishell environment. it could be a list but хз
	int	ex_code;//this is the exit code of the last command.
	t_logical_groups	*first_group;
}	t_minishell_environment;

typedef struct s_fds {
	int	infile;
	int	outfile;
	char	re_flag;
	int	r_code;
	pid_t	pid_com;
	struct s_fds	*next_fd;
}	t_fds;

typedef struct s_exec_env {
	int	**_pipes;
	char	**envp_in;
	t_fds	*first_fd;
}	t_exec_env;

int	executor(t_minishell_environment *min_environment);
int	ft_init(t_logical_groups *group, t_exec_env *in_exec);
int	open_pipes(t_logical_groups *group, t_exec_env *in_exec);
int	alloc_pipes(int ***pipes, int num);
int	ft_free(t_logical_groups *group, t_exec_env *in_exec);
void	free_min_env(t_logical_groups *group);
int	alloc_lsts(t_exec_env *in_exec, int num);
int	create_lst(t_fds **lst);
void	free_lsts(t_fds *lst);
int	open_files(t_command_list *commands, t_fds *fds);

int	run_commands(t_logical_groups *group, t_exec_env *in_exec);
void	ft_exec(t_logical_groups *group, t_command_list *cmd, t_exec_env *in_exec, int i);
void	create_pipeline(int	**pipes, int com, int length);
void	swap_filedescriptors(t_exec_env *in_exec, int com);

void	close_pipes(t_exec_env *in_exec, int num);
int	ft_wait(t_exec_env *in_exec);
int	ft_kill(t_exec_env *in_exec);
void	save_ex_code(t_minishell_environment *min_environment, t_exec_env *in_exec);

#endif
