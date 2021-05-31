#include "minishell.h"

void	error_handler(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
}

void	init(t_data *data, char **env)
{
	data->syn_error = 0;
	data->env = env;
	data->cmd_count = 0;
	data->str = NULL;
}

void	set_promt()
{
	write(1, "\e[32mminishell> \e[0m", 20);
}

void	free_cmd_lines(char ***cmd_lines, char **str)
{
	int	i;
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
		free(cmd_lines);
	if (*str)
		free(*str);
	*str = NULL;
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
			make_string(&data->str, c);
		parsing(data);
		free_cmd_lines(data->cmd_lines, &data->str);
	}
}