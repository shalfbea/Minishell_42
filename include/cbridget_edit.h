/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbridget_edit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:57:43 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/28 18:43:20 by cbridget         ###   ########.fr       */
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
	char	*command;//absolut path to the command???
	char	**argv;//command arguments. last pointer must be NULL;
	t_command_list	*next_command;//if there are no more commands, set to NULL.
}	t_command_list;//linked list for commands.

typedef struct s_executor_environment {
	char	**envp;//minishell environment. it could be a list but хз
	int		number_of_commands;//number of commands to execute
	t_command_list	*first_command;//poiter to the first command to execute
}	t_executor_environment;

#endif
