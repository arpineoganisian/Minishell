#include "minishell.h"

void	cmd_not_found(char *cmd_line)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd_line, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd("command not found", 1);
	exit_status = 127;
}

void	fork_process(char *path_to_bin, char **cmd_line, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(path_to_bin, cmd_line, data->envp);
	else
		waitpid(pid, &status, 0);
}

void	execute_bin(char **cmd_line, t_data *data)
{
	char	**paths;
	int		i;
	char	*path_to_bin;
	int 	flag;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	flag = 0;
	while (paths[i])
	{
		//TODO после проверки всех путей, проверить еще и просто cmd_line[0]
		path_to_bin = ft_strjoin(paths[i], ft_strjoin("/", cmd_line[0]));
		if (open(path_to_bin, O_RDONLY) != -1) //проверка open и stat
			//close(fd) ?
		{
			fork_process(path_to_bin, cmd_line, data);
			flag = 1;
		}
		free(path_to_bin);
		i++;
	}
	free(paths);
	if (!flag)
		cmd_not_found(cmd_line[0]);
}
