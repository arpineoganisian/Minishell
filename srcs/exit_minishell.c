#include "minishell.h"

void exit_minishell()
{
	//todo команда exit 1 выходит с exit_status 1 (получить аргументы и
	// отправить в exit_status)
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_status);
}
