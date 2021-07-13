#include "minishell.h"

int	export(char **cmd_line, t_data *data)
{
	int i;

	i = strings_counter(data->envp);
	if (strings_counter(cmd_line) == 1)
		return (0);
	if (cmd_line[1][0] == '=')
	{
		error_handler(ft_strjoin(ft_strjoin("export: `",
			cmd_line[1]), "': not a valid identifier"), 1);
		return (1);
	}
	//TODO перезаписать переменную если такая существует
	if (ft_strchr(cmd_line[1], '=') != NULL)
	{
		data->envp[i] = cmd_line[1];
		data->envp[i + 1] = NULL;
	}
	return (0);
}