#include "minishell.h"

void	error_handler(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
}

void	init(t_data *data, char **env)
{
	data->syn_error = 0;
	data->cmd = malloc(sizeof(char) * 1024);
	data->arg = malloc(sizeof(char) * 1024);
	data->env = env;
	data->cmd_count = 0;
	data->str = NULL;
}

void	set_promt()
{
	write(1, "\e[32mminishell> \e[0m", 20);
}
int		main(int argc, char **argv, char **env)
{
	t_data 	*data;
	char	c;
	(void)argc;
	(void)argv;

	data = (t_data *) malloc(sizeof(t_data));
	init(data, env);
	while (1)
	{
		set_promt();
		while (read(0, &c, 1) && c != '\n')
			data->str = make_string(data->str, c);
		parsing(data);
	}
}