
#include "minishell.h"

char **init_env(char **env);

int	main(int argc, char **argv, char **envp)
{
	t_command_list *commands;
	argc = 0;
	argv = NULL;
/*	char *envp[] = {"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.k9YvMHCGX1/Render",
			"COLORFGBG=15;0",
			"ITERM_PROFILE=Default",
			"XPC_FLAGS=0x0",
			"LANG=en_US.UTF-8",
			"PWD=/Users/cbridget/minishell2/cbridgetf",
			"SHELL=/bin/zsh",
			"PAGER=less",
			"SECURITYSESSIONID=186d0",
			"TERM_PROGRAM_VERSION=3.4.15",
			"TERM_PROGRAM=iTerm.app",
			"PATH=/Users/cbridget/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:/opt/X11/bin:~/.dotnet/tools",
			"DISPLAY=/private/tmp/com.apple.launchd.ShEeMlc4qc/org.xquartz:0", NULL};*/
	g_ms_env.envp = init_env(envp);
	g_ms_env.ex_code = 0;
	g_ms_env.pids = NULL;
	init_builtins();
/*	char *t[2];
	t[0] = malloc(8);
	t[0][0] = 'e';
	t[0][1] = 'n';
	t[0][2] = 'v';
	t[0][3] = '\0';
	t[0][4] = 'r';
	t[0][5] = 't';
	t[0][6] = '\0';
	t[1] = NULL;*/
	char *t[] = {"env", NULL};
	ft_env(t);
	int len = 0;
	while (g_ms_env.envp[len])
		len++;
	printf("\nlen=%d\n", len);
	char *t2[] = {"unset", "8dlfj=5", "PAGER=", "hello", "PAGER", "world=33", NULL};
	char *vector[] = {NULL};
	char v_flags[] = {2, 3, 3};
	g_ms_env.number_of_commands = 1;
	commands = malloc(sizeof(t_command_list) * 1);
	commands->argv = t2;
	commands->redirects = vector;
	commands->redirect_flags = v_flags;
	commands->next_command = NULL;
/*	char *t2[] = {"export", "8dlfj=5", "1234=888", NULL};
	char *vector1[] = {NULL};
	char v_flags1[] = {0, 0, 3};
	commands->next_command = malloc(sizeof(t_command_list) * 1);
	commands->next_command->argv = t2;
	commands->next_command->redirects = vector1;
	commands->next_command->redirect_flags = v_flags1;
	commands->next_command->next_command = NULL;
	char *t3[] = {"env", NULL};
	char *vector2[] = {NULL};
	char v_flags2[] = {0, 0, 3};
	commands->next_command->next_command = malloc(sizeof(t_command_list) * 1);
	commands->next_command->next_command->argv = t3;
	commands->next_command->next_command->redirects = vector2;
	commands->next_command->next_command->redirect_flags = v_flags2;
	commands->next_command->next_command->next_command = NULL;*/
	executor(commands);
	ft_env(t);
	len = 0;
	while (g_ms_env.envp[len])
		len++;
	printf("\nlen=%d\n", len);
	printf("ex_code=%d\n", g_ms_env.ex_code);
//	free(t[0]);
//	free(commands->next_command);
	free(commands);
	free_vector(g_ms_env.envp);
	return (0);
}

char **init_env(char **env)
{
	char **tmp_env;
	int	length = 0;
	while (env[length])
		length++;
	tmp_env = malloc(sizeof(char *) * (length + 1));
	int i = 0;
	while (env[i])
	{
		tmp_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp_env[length] = NULL;
	return (tmp_env);
}
