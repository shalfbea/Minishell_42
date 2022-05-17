
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell_environment	test;
	t_logical_groups	test_g;
	test.first_group = &test_g;

	argc = 0;
	argv = NULL;
	test.envp = envp;
	init_builtins(&test);
//	char *t[] = {"cd", "../shalfbea", NULL};
	char *t[2];
	t[0] = malloc(6);
	t[0][0] = 'y';
	t[0][1] = 'e';
	t[0][2] = 's';
	t[0][3] = '\0';
	t[1] = NULL;
	char *vector[] = {NULL};
	char v_flags[] = {2, 3, 3};
	test.first_group->number_of_commands = 2;
	test.first_group->first_command = malloc(sizeof(t_command_list) * 1);
	test.first_group->first_command->argv = t;
	test.first_group->first_command->redirects = vector;
	test.first_group->first_command->redirect_flags = v_flags;
	test.first_group->first_command->next_command = NULL;
	char *t2[] = {"/bin/cat", NULL};
	char *vector1[] = {"outfile", NULL};
	char v_flags1[] = {0, 0, 3};
	test.first_group->first_command->next_command = malloc(sizeof(t_command_list) * 1);
	test.first_group->first_command->next_command->argv = t2;
	test.first_group->first_command->next_command->redirects = vector1;
	test.first_group->first_command->next_command->redirect_flags = v_flags1;
	test.first_group->first_command->next_command->next_command = NULL;
/*	char *t3[] = {"/bin/cat", "slfi", NULL};
	test.first_group->first_command->next_command->next_command = malloc(sizeof(t_command_list) * 1);
//	test.first_group->first_command->next_command->next_command->command = "/bin/cat";
	test.first_group->first_command->next_command->next_command->infile = NULL;
	test.first_group->first_command->next_command->next_command->outfile = "outfile";
	test.first_group->first_command->next_command->next_command->redirect_flag_infile = 0;
	test.first_group->first_command->next_command->next_command->redirect_flag_outfile = 1;
	test.first_group->first_command->next_command->next_command->argv = t3;
	test.first_group->first_command->next_command->next_command->next_command = NULL;*/
/*	char *str;
	str = getcwd(NULL, 0);
	printf("before=%s\n", str);
	free(str);*/
	executor(&test);
//	str = getcwd(NULL, 0);
//	printf("after=%s\n", str);
//	free(str);
//	check_cmd("cat", envp);
	printf("ex_code=%d\n", test.ex_code);
//	free(t[0]);
//	free(test.first_group->first_command->next_command);
	free(test.first_group->first_command);
/*	int **test;
	test = malloc(sizeof(int *) * 4);
	test[0] = malloc(sizeof(int) * 3 * 2);
	test[1] = test[0] + 1 * 2;
	test[2] = test[0] + 2 * 2;
	test[3] = (void *)0;
	int i = 0;
	while (i < 4)
	{
		create_pipeline(test, i + 1, 4);
		i++;
	}*/
	return (0);
}
