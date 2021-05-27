#include "minishell.h"

void	read_stdin(char *buf)
{
	read(0, buf, 1024);
}

void	parse_cmd(char *buf, t_parsing_data *parsing_data, int *i)
{
	int	j;

	j = 0;
	while (buf[*i] != ' ' && buf[*i] != ';' && buf[*i] != '\n')
	{
		parsing_data->cmd[j] = buf[*i];
		(*i)++;
		j++;
	}
	parsing_data->cmd[j] = '\0';
}

void	parse_arg(char *buf, t_parsing_data *parsing_data, int *i)
{
	int	j;

	j = 0;
	while (buf[*i] != ' ' && buf[*i] != ';' && buf[*i] != '\n')
	{
		parsing_data->arg[j] = buf[*i];
		(*i)++;
		j++;
	}
	parsing_data->arg[j] = '\0';
}

void	parsing(char *buf, t_parsing_data *parsing_data)
{
	int		i;

	buf = spec_sym_handler(buf);
	i = 0;
	while (buf[i] != '\n')
	{
		while (buf[i] == ' ')
			i++;
		parse_cmd(buf, parsing_data, &i);
		while (buf[i] == ' ')
			i++;
		if (buf[i] == '-')
			if (buf[i + 1] == 'n')
			{
				parsing_data->flag = 1;
				i += 2;
			}
		while (buf[i] == ' ')
			i++;
		parse_arg(buf, parsing_data, &i);
		if (buf[i] == ';')
			execute_cmd(parsing_data);
		if (buf[i] != '\n')
			i++;
	}
}

void	reading_parsing(char *buf, t_parsing_data *parsing_data)
{
	read_stdin(buf);
	parsing_data->syn_error = preparsing(buf);
	if (!parsing_data->syn_error)
		parsing(buf, parsing_data);
}