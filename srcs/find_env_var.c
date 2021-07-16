#include "minishell.h"

int	find_env_var(char *var, char **env_vars)
{
	int	i;

	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(var, env_vars[i], ft_strlen(var)) == 0 && env_vars[i][ft_strlen(var)] == '=')
			return (i);
		i++;
	}
	return (-1);
}