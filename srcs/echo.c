#include "minishell.h"

int		check_flag(char **cmd_line, int *i)
{
	int flag_n;
	int j;

	flag_n = 0;
	j = 2;
	if (ft_strncmp(cmd_line[*i], "-n", 2) != 0)
		return flag_n;
	if (ft_strncmp(cmd_line[*i], "-n", 2) == 0)
	{
		while(cmd_line[*i][j])
		{
			if (cmd_line[*i][j] != 'n')
				return flag_n;
			j++;
		}
		flag_n = 1;
	}
	(*i)++;
	while(cmd_line[*i])
	{
		j = 2;
		if (ft_strncmp(cmd_line[*i], "-n", 2) == 0)
		{
			while(cmd_line[*i][j])
			{
				if (cmd_line[*i][j] != 'n')
					break;
				j++;
			}
		}
		(*i)++;
	}


	return flag_n;
}

void    echo(char **cmd_line)
{
	int i;
	int flag_n;
	int strings_amount;

	strings_amount = strings_counter(cmd_line);
	if (strings_amount == 1)
	{
		write(1, "\n", 1);
		return;
	}
	i = 1;
	flag_n = check_flag(cmd_line, &i);
	while (i < strings_amount && cmd_line[i])
	{
		ft_putstr_fd(cmd_line[i], 1);
		i++;
		if (i != strings_amount)
			write(1, " ", 1);
	}
	if (!flag_n)
		write(1, "\n", 1);
}