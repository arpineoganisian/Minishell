#include "minishell.h"

int	find_env_var(char *key, char **env_vars)
{
	int	i;

	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(key, env_vars[i], ft_strlen(key)) == 0 && env_vars[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}