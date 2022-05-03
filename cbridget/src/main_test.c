
#include "minishell.h"

int	main(void)
{
/*	t_minishell_environment	test;

	test.envp = NULL;
	test.number_of_commands = 3;
	test.first_command = malloc(sizeof(t_command_list) * 1);
	test.first_command->command = "/bin/echo";
	test.first_command->infile = "infile1";
	test.first_command->outfile = "outfile1";
	test.first_command->redirect_flag_infile = 0;
	test.first_command->redirect_flag_outfile = 0;
	test.first_command->argv = NULL;
	test.first_command->next_command = malloc(sizeof(t_command_list) * 1);
	test.first_command->next_command->command = "/bin/cat";
	test.first_command->next_command->infile = "infile2";
	test.first_command->next_command->outfile = "outfile2";
	test.first_command->next_command->redirect_flag_infile = 0;
	test.first_command->next_command->redirect_flag_outfile = 0;
	test.first_command->next_command->argv = NULL;
	test.first_command->next_command->next_command = NULL;
	test.first_command->next_command->next_command = malloc(sizeof(t_command_list) * 1);
	test.first_command->next_command->next_command->command = "/bin/cat";
	test.first_command->next_command->next_command->infile = "infile3";
	test.first_command->next_command->next_command->outfile = "outfile3";
	test.first_command->next_command->next_command->redirect_flag_infile = 0;
	test.first_command->next_command->next_command->redirect_flag_outfile = 0;
	test.first_command->next_command->next_command->argv = NULL;
	test.first_command->next_command->next_command->next_command = NULL;
	executor(&test);*/

	int test[3];
	ft_close_fd(test, 2, 4);
	return (0);
}
