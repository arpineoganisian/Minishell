#include "minishell.h"

char	**sort_envp(char **envp)
{
	int		i;
	int		j;
	char	**sorted;
	int		n;
	char	*tmp;

	i = 0;
	n = strings_counter(envp);
	sorted = copy_envp(envp);
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(sorted[i], sorted[j], ft_strlen(sorted[i])) > 0)
			{
				tmp = ft_strdup(sorted[i]);
				free(sorted[i]);
				sorted[i] = ft_strdup(sorted[j]);
				free(sorted[j]);
				sorted[j] = ft_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

void	print_export(char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;

	while(envp[i])
	{
//		while();
		i++;
	}
	free(envp);
}

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
	i = find_env_var(key, data->envp);
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
	if (strings_counter(cmd_line) == 1)
	{
		print_export(sort_envp(data->envp));
		return (0);
	}
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
