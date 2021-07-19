#include "minishell.h"

void	change_envp_oldpwd(char *key, char *value, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str_3_join(key, "=", value);
	while (data->envp[i])
	{
		if (ft_strncmp(key, data->envp[i], ft_strlen(key)) == 0)
		{
			ft_strlcpy(data->envp[i], tmp, (ft_strlen(tmp) + 1));
			free(tmp);
			return ;
		}
		i++;
	}
	ft_strlcpy(data->envp[i], tmp, (ft_strlen(tmp) + 1));
	free(tmp);
}

void	change_envp_pwd(char *key, char *value, t_data *data)
{
	char	*tmp;

	tmp = str_3_join(key, "=", value);
	if (check_and_change_env_vars(tmp, data) == -1)
		add_env_var(data, tmp);
	free(tmp);
}
