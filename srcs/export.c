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
	int		flag;

	i = 0;
	flag = 0;

	while (envp[i])
	{
		j = 0;
		flag = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (envp[i][j])
		{
			if (!flag && envp[i][j] == '=')
			{
				write(STDOUT_FILENO, "=\"", 2);
				flag = 1;
			}
			else
				write(STDOUT_FILENO, &envp[i][j], 1);
			j++;
		}
		if (ft_strncmp(envp[i], "OLDPWD", 6))
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	free(envp);
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
