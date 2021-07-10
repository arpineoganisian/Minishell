#include "minishell.h"

void	cmd_not_found(char *cmd_line)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd_line, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd("command not found", 1);
	exit_status = 127;
}

void	execute_bin(char **cmd_line, t_data *data)
{
	char	**paths;
	int		i;
	char	*path_to_bin;
	pid_t	pid;
	int		status;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (paths[i])
		{
			path_to_bin = ft_strjoin(paths[i], ft_strjoin("/", cmd_line[0]));
			execve(path_to_bin, cmd_line, data->envp);
			free(path_to_bin);
			i++;
		}
		cmd_not_found(cmd_line[0]);
	}
	waitpid(pid, &status, 0);
}
