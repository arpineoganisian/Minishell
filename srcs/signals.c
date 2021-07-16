#include "minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_d(t_data *data)
{
	ft_putstr_fd("\e[1F\e[12G", 1);
	exit_status = 1;
	exit_minishell(data);
}

void	ctrl_c_herdoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\e[1F\e[1G\e[0K", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

void	ctrl_c_child(int sig)
{
	(void)sig;
	ft_putstr_fd("hello", STDOUT_FILENO);
	ft_putstr_fd("\e[1F\e[1G\e[0K", 1);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}
