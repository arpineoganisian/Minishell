#include "minishell.h"

int exit_minishell(char **cmd_line)
{
	unsigned char exit_arg;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd_line)
	{
		if (strings_counter(cmd_line) > 2)
		{
			error_handler("exit: too many arguments", 1);
			return 1;
		}
		else if (strings_counter(cmd_line) == 2)
		{
			exit_arg = ft_atoi(cmd_line[1]);
			exit_status = exit_arg;
		}
	}
	exit(exit_status);

}
