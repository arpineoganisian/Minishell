#include "minishell.h"

int cd_home()
{
	int chdir_ret_val;
	char *home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return 1;
	}
	chdir_ret_val = chdir(home);
	if (chdir_ret_val == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return 1;
	}
	return 0;
}

int cd(char **cmd_line, t_data *data)
{
	int chdir_ret_val;
	char	*error;
	char	*tmp;

	if (strings_counter(cmd_line) == 1)
		return cd_home();
	chdir_ret_val = chdir(cmd_line[1]);
	if (chdir_ret_val == -1)
	{
		tmp = ft_strjoin("cd: ", cmd_line[1]);
		error = ft_strjoin(tmp, ": ");
		error_handler(ft_strjoin(error, strerror(errno)), data, 1);
		free(tmp);
		free(error);
		return 1;
	}
	return 0;
}