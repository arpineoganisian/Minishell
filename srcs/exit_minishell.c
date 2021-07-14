#include "minishell.h"

void exit_minishell()
{
	ft_putendl_fd("exit", 1);
	exit(exit_status);
}