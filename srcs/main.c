#include "minishell.h"

void	error_handler(char *str, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
	exit_status = status;
}

void ctrl_c(int sig)
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

void	init(t_data *data, char **envp)
{
	data->line_read = NULL;
	data->fd_out[0] = STDOUT_FILENO;
	data->fd_in[0] = STDIN_FILENO;
	data->fd_out[1] = dup(STDOUT_FILENO);
	data->fd_in[1] = dup(STDIN_FILENO);
	data->heredoc = NULL;
	data->fd_heredoc = 0;
	exit_status = 0;
	data->envp = envp;
	data->envp_exp = copy_envp(envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d()
{
	ft_putstr_fd("\e[1F\e[12G", 1);
	exit_status = 1;
	exit_minishell()
}

int		main(int argc, char **argv, char **envp)
{
	t_data 	*data;
	(void)argc;
	(void)argv;

	data = (t_data *) malloc(sizeof(t_data));
	init(data, envp);
	while (1)
	{
		data->line_read = readline_history("\e[32mminishell> \e[0m",
										   data->line_read);
		if (!data->line_read)
			ctrl_d();
		if (data->line_read && *data->line_read)
			parsing(data);
	}
}