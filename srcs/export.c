#include "minishell.h"

int	check_and_change_env_vars(char *cmd_line, t_data *data)
{
	char	*key;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while(cmd_line[++i])
	{
		if (cmd_line[i] == '=')
			break;
	}
	key = ft_substr(cmd_line, 0, i);
	i = find_env_var(key, data);
	if (i == -1)
		ret = -1;
	else
	{
		data->envp[i] = cmd_line;
		free(data->envp_exp[i]);
		data->envp_exp[i] = ft_strdup(cmd_line);
	}
	free(key);
	return (ret);
}

void	add_env_var(t_data *data, char *cmd_line)
{
	int	i;

	i = strings_counter(data->envp);
	data->envp[i] = cmd_line;
	data->envp[i + 1] = NULL;
	data->envp_exp = arrjoin(data->envp_exp, cmd_line);
}

int	export(char **cmd_line, t_data *data)
{
	//todo вывод просто команды export
	if (strings_counter(cmd_line) == 1)
		return (0);
	if (cmd_line[1][0] == '=')
	{
		error_handler(ft_strjoin(ft_strjoin("export: `", cmd_line[1]), "': not a valid identifier"), 1);
		return (1);
	}
	if (ft_strchr(cmd_line[1], '=') != NULL && check_and_change_env_vars(cmd_line[1], data) == -1)
	{
		add_env_var(data, cmd_line[1]);
	}
	return (0);
}
