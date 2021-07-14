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
	if (pid == -1)
		//TODO какой должен быть exit status?
		error_handler(strerror(errno), -1);
	else if (pid == 0)
		execve(path_to_bin, cmd_line, data->envp_exp);
	else
		waitpid(pid, &status, 0);
}

int check_paths(char *path_to_bin)
{
	int fd;
	struct stat sb;
	int res;

	res = -1;
	fd = open(path_to_bin, O_RDONLY);
	if (fd != -1 && stat(path_to_bin, &sb) == 0 && sb.st_mode & S_IXUSR)
		res = 0;
	close(fd);
	return (res);
}

void	execute_bin(char **cmd_line, t_data *data)
{
	char	**paths;
	int		i;
	char	*path_to_bin;
	int 	flag;

	i = 0;
	flag = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		path_to_bin = ft_strjoin(paths[i], ft_strjoin("/", cmd_line[0]));
		if (check_paths(path_to_bin) == 0)
		{
			fork_process(path_to_bin, cmd_line, data);
			flag = 1;
		}
		free(path_to_bin);
		i++;
	}
	free(paths);
	if (!flag && check_paths(cmd_line[0]) == 0)
		fork_process(cmd_line[0], cmd_line, data);
	else if (!flag)
		cmd_not_found(cmd_line[0]);
}
