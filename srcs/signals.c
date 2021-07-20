#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	exit_status = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_child(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit_status = 130;
}

void	ctrl_d()
{
	ft_putstr_fd("\e[1F\e[12G", 1);
	exit_minishell(NULL);
}

void	ctrl_slash_child(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	exit_status = 131;
}
