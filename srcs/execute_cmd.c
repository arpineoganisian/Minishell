#include "minishell.h"

void	execute_cmd(char **cmd_line, t_data *data)
{
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen(cmd_line[0])))
		echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen(cmd_line[0])))
		cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen(cmd_line[0])))
		pwd();
	else if (!ft_strncmp(cmd_line[0], "export", ft_strlen(cmd_line[0])))
		export(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "unset", ft_strlen(cmd_line[0])))
		unset(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "env", ft_strlen(cmd_line[0])))
		env(data);
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen(cmd_line[0])))
		exit(exit_status);
	else
		execute_bin(cmd_line, data);
	if (data->fd_out[0] != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(data->fd_out[1], STDOUT_FILENO);
	}
	if (data->fd_in [0] != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(data->fd_in[1], STDIN_FILENO);
	}
}