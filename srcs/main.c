#include "minishell.h"

void change_shlvl(t_data *data)
{
	char	*shlvl;
	int		new_shlvl;
	int 	i;

	shlvl = get_minishell_env("SHLVL", data->envp);
	if (!shlvl)
		new_shlvl = 1;
	else
	{
		new_shlvl = ft_atoi(shlvl);
		if (new_shlvl < 0)
			new_shlvl = 0;
		else
			new_shlvl++;
	}
	i = find_env_var("SHLVL", data->envp);
	free(shlvl);
	shlvl = ft_itoa(new_shlvl);
	data->envp[i] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
}

void	error_handler(char *str, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
	exit_status = status;
}

void	init(t_data *data, char **envp)
{
	data->line_read = NULL;
	data->fd_out[0] = STDOUT_FILENO;
	data->fd_in[0] = STDIN_FILENO;
	data->fd_out[1] = dup(STDOUT_FILENO);
	data->fd_in[1] = dup(STDIN_FILENO);
	exit_status = 0;
	data->envp = envp;
	change_shlvl(data);
	data->envp_exp = copy_envp(envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = (t_data *) malloc(sizeof(t_data));
	init(data, envp);
	while (1)
	{
		data->line_read = readline_history("\e[32mminishell> \e[0m",
				data->line_read);
		if (!data->line_read)
			ctrl_d(data);
		if (data->line_read && *data->line_read)
			parsing(data);
	}
}
