#include "minishell.h"

void	error_handler(char *str, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
	exit_status = status;
}
