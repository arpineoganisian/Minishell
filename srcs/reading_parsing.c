#include "minishell.h"

void	read_stdin(char *buf)
{
	read(0, buf, 1024);
}

void	parse_command(char *buf, t_parsing_data *parsing_data)
{
	int		i;
	int 	j;

	i = 0;
	while (buf[i])
	{
		while (buf[i] == ' ')
			i++;
		j = 0;
		while (buf[i] != ' ' && buf[i] != ';' && buf[i] != '\0')
		{
			parsing_data->cmd[j] = buf[i];
			i++;
			j++;
		}
		parsing_data->cmd[j] = '\0';
		while (buf[i] == ' ')
			i++;
		if (buf[i] == ';')
			execute_cmd(parsing_data);
		if (buf[i])
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