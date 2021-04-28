#include "minishell.h"

void	read_stdin(char *buf)
{
	read(0, buf, 1024);
}

void	parse_command(char *buf, t_parsing_data *parsing_data)
{
	int		i;

	i = 0;
	while ((buf[i] != ' ' && buf[i] != '\0') || i < 1023)
	{
		parsing_data->cmd[i] = buf[i];
		i++;
	}
	parsing_data->cmd[i] = '\0';
}

void	parsing(char *buf, t_parsing_data *parsing_data)
{
	parse_command(buf, parsing_data);
}

void	reading_parsing(char *buf, t_parsing_data *parsing_data)
{
	read_stdin(buf);
	parsing(buf, parsing_data);
}