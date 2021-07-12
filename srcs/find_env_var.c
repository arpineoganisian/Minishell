#include "minishell.h"

int	find_env_var(char *var, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(var, data->envp[i], ft_strlen(var)) == 0
			&& data->envp[i][ft_strlen(var)] == '=')
			return (i);
		i++;
	}
	return (-1);
}