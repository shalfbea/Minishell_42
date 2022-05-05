/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/05/05 16:21:32 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBRIDGET_EDIT_H
# define CBRIDGET_EDIT_H

//Put your own things here, to protect minishell_h

typedef struct s_command_list {
	char	build_in_flag;//????
	char	redirect_flag_infile;// 0 means: redirect >, 1 means: redirect >>.
	char	*infile;//pointer to a string with named infile, NULL means no file.
	char	redirect_flag_outfile;// same as redirect_flag_infile but for outfile.
	char	*outfile;//same as *infile but for outfile.
//	char	*command;//absolut path to the command???
	char	**argv;//first pointer is the absolut path to the command. command arguments. last pointer must be NULL;
	struct s_command_list	*next_command;//if there are no more commands, set to NULL.
}	t_command_list;//linked list for commands.

typedef struct s_minishell_environment {
	char	**envp;//minishell environment. it could be a list but хз
	int		number_of_commands;//number of commands to execute
	t_command_list	*first_command;//poiter to the first command to execute
}	t_minishell_environment;

typedef struct s_fds {
	int	infile;
	int	outfile;
	pid_t	pid_com;
	struct s_fds	*next_fd;
}	t_fds;

typedef struct s_exec_env {
	int	**_pipes;
	t_fds	*first_fd;
}	t_exec_env;

int	executor(t_minishell_environment *min_environment);
int	ft_init(t_minishell_environment *min_environment, t_exec_env *in_exec);
int	open_pipes(t_minishell_environment *min_environment, t_exec_env *in_exec);
int	alloc_pipes(int ***pipes, int num);
int	ft_free(t_minishell_environment *min_environment, t_exec_env *in_exec);
void	free_min_env(t_minishell_environment *min_environment);
int	alloc_lsts(t_exec_env *in_exec, int num);
int	create_lst(t_fds **lst);
void	free_lsts(t_fds *lst);
int	open_files(t_command_list *commands, t_fds *fds);

int	run_commands(t_minishell_environment *min_environment, t_exec_env *in_exec);
void	ft_exec(t_minishell_environment *min_environment, t_command_list *cmd, t_exec_env *in_exec, int i);
void	create_pipeline(int	**pipes, int com, int length);

#endif
