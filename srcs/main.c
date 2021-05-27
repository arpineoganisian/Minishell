#include "minishell.h"

void	error_handler(char *str)
{
	ft_putstr_fd("minishell: ", 0);
	ft_putendl_fd(str, 0);
}

void	init(t_parsing_data *parsing_data)
{
	parsing_data->syn_error = 0;
	parsing_data->cmd = malloc(sizeof(char) * 1024);
	parsing_data->arg = malloc(sizeof(char) * 1024);

}

void	set_promt()
{
	write(1, "\e[32mminishell> \e[0m", 20);
}
int		main(int argc, char **argv, char **envp)
{
	char			buf[1024];
	t_parsing_data	*parsing_data;
	(void)argc;
	(void)argv;
	(void)envp;

	parsing_data = (t_parsing_data *) malloc(sizeof(t_parsing_data));
	init(parsing_data);
	while (1)
	{
		set_promt();
		reading_parsing(buf, parsing_data);
		if (!parsing_data->syn_error)
			execute_cmd(parsing_data);
	}
}