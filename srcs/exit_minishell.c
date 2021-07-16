#include "minishell.h"

void exit_minishell()
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_status);
}
