#include "minishell.h"

void	error_handler(char *str)
{
	ft_putstr_fd("minishell: ", 0);
	ft_putendl_fd(str, 0);

}

void ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	init(t_data *data)
{
	data->line_read = NULL;
	data->fd_out = 1;
	data->fd_in = 0;
	data->heredoc = NULL;
	data->fd_heredoc = 0;
	data->exit_status = 0;
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	free_cmd_lines(char ***cmd_lines, char **str)
{
	(void)cmd_lines;
	/*int	i;
	int	k;

	i = 0;
	while (cmd_lines[i])
	{
		k = 0;
		while (cmd_lines[i][k])
		{
			free(cmd_lines[i][k]);
			k++;
		}
		free(cmd_lines[i]);
		i++;
	}
	if (cmd_lines)
		free(cmd_lines);*/
	if (*str)
		free(*str);
	*str = NULL;
}

int		main(void)
{
	t_data 	*data;

	data = (t_data *) malloc(sizeof(t_data));
	init(data);
	while (1)
	{
		data->line_read = readline_history("\e[32mminishell> \e[0m",
										   data->line_read);
		if (!data->line_read)
		{
			ft_putstr_fd("\e[1F\e[12G", 1);
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		if (data->line_read && *data->line_read)
			parsing(data);
		//free_cmd_lines(data->cmd_lines, &data->line_read);
	}
}