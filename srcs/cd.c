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

int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int cd(char **cmd_line)
{
	if (strings_counter(cmd_line) == 1)
		return (cd_home());
	if (chdir(cmd_line[1]) == -1)
	{
		cd_err_handler("cd: ", ": ", cmd_line[1]);
		return (1);
	}
	return (0);
}
