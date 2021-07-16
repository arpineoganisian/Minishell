#include "minishell.h"

int	unset(char **cmd_line, t_data *data)
{
	int	i;
	int num_of_envp;

	if (strings_counter(cmd_line) == 1)
		return (0);
	i = find_env_var(cmd_line[1], data->envp);
	if (i == -1)
		return (0);
	num_of_envp = strings_counter(data->envp);
	while (num_of_envp - i > 0)
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	data->envp[i] = NULL;
	return (0);
}