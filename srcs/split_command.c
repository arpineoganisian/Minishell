#include "minishell.h"

void	split_cmd(t_data *data)
{
	char	**tmp;
	int	i;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == ';')
			data->cmd_count++;
		i++;
	}
	data->cmd_lines = (char ***)malloc(sizeof(char **) * (data->cmd_count + 2));
	tmp = ft_split(data->str, ';');
	i = 0;
	while (tmp[i])
	{
		data->cmd_lines[i] = ft_split(tmp[i], ' ');
		execute_cmd(data->cmd_lines[i]);
		i++;
	}
	data->cmd_lines[i] = NULL;
}
