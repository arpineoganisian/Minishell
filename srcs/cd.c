#include "minishell.h"

void	cd_err_handler(char *str1, char *str2, char *cmd_line)
{
	char	*error;
	char	*tmp;

	tmp = ft_strjoin(str1, cmd_line);
	error = ft_strjoin(tmp, str2);
	error_handler(ft_strjoin(error, strerror(errno)), 1);
	free(tmp);
	free(error);
}

int	cd_home(t_data *data)
{
	char	*home;

	home = get_minishell_env("HOME", data->envp);
	if (!home)
	{
		error_handler("cd: HOME not set", 1);
		return (1);
	}
	if (chdir(home) == -1)
	{
		//bash: cd: 1111: No such file or directory
		//TODO написать для джойнов строчек для ошибок
		error_handler(ft_strjoin(ft_strjoin("cd: ", home), strerror(errno)), 2);
		return (1);
	}
	free(home);
	return (0);
}

int cd(char **cmd_line, t_data *data)
{
	if (strings_counter(cmd_line) == 1)
		return (cd_home(data));
	if (chdir(cmd_line[1]) == -1)
	{
		cd_err_handler("cd: ", ": ", cmd_line[1]);
		return (1);
	}
	return (0);
}
