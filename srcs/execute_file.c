#include "minishell.h"

void	execute_file(char **cmd_line, t_data *data)
{
	char **paths;
	int i;
	char *tmp;
	char *path_to_bin;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", cmd_line[0]);
		path_to_bin = ft_strjoin(paths[i], tmp);
		free(tmp);
		execve(path_to_bin, cmd_line, data->envp);
		free(path_to_bin);
		i++;
	}
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd_line[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd("command not found", 1);
	exit_status = 127;
}