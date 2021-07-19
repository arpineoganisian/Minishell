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

int	find_env_var_without_equals_sign(char *key, char **env_vars)
{
	int	i;

	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(key, env_vars[i], ft_strlen(key)) == 0 && (env_vars[i][ft_strlen(key)] == '=' || env_vars[i][ft_strlen(key)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	add_env_var(t_data *data, char *cmd_line)
{
	int	i;

	i = strings_counter(data->envp);
	data->envp[i] = ft_strdup(cmd_line);
	data->envp[i + 1] = NULL;
	if (ft_strchr(cmd_line, '='))
		data->envp_exp = join_str_to_arr(data->envp_exp, cmd_line);
}

int	check_and_change_env_vars(char *cmd_line, t_data *data)
{
	char	*key;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while(cmd_line[++i])
		if (cmd_line[i] == '=')
			break;
	key = ft_substr(cmd_line, 0, i);
	i = find_env_var_without_equals_sign(key, data->envp);
	if (i == -1)
		ret = -1;
	else if (ft_strchr(cmd_line, '='))
	{
		ft_strlcpy(data->envp[i], cmd_line, ft_strlen(cmd_line) + 1);
		free(data->envp_exp[i]);
		data->envp_exp[i] = ft_strdup(cmd_line);
	}
	free(key);
	return (ret);
}