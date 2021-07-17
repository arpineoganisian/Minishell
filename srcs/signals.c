#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(t_data *data)
{
	ft_putstr_fd("\e[1F\e[12G", 1);
	exit_status = 1;
	exit_minishell(data);
}
