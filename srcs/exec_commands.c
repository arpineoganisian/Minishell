#include "minishell.h"

void	exec_cmd(char **cmd_line, t_data *data)
{
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen(cmd_line[0])))
		echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen(cmd_line[0])))
		cd(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen(cmd_line[0])))
		pwd();
	else if (!ft_strncmp(cmd_line[0], "export", ft_strlen(cmd_line[0])))
		export(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "unset", ft_strlen(cmd_line[0])))
		unset(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "env", ft_strlen(cmd_line[0])))
		env(data);
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen(cmd_line[0])))
		exit_minishell();
	else
		execute_bin(cmd_line, data);
}

void	exec_commands(t_data *data, int i, int tokens_count)
{
	if (i != 0)
	{
		data->fd_in[0] = data->fd_in_next;
		dup2(data->fd_in[0], STDIN_FILENO);
	}
	if (i < tokens_count - 1 && data->fd_out[0] == STDOUT_FILENO)
	{
		pipe(data->fd);
		data->fd_out[0] = data->fd[1];
		data->fd_in_next = data->fd[0];
		dup2(data->fd_out[0], STDOUT_FILENO);
	}
	exec_cmd(data->cmd_lines[i], data);
	if (data->fd_out[0] != STDOUT_FILENO)
	{
		close(data->fd_out[0]);
		dup2(data->fd_out[1], STDOUT_FILENO);
		data->fd_out[0] = STDOUT_FILENO;
		if (i < tokens_count - 1)
			close(data->fd_in_next);
	}
	if (data->fd_in[0] != STDIN_FILENO)
	{
		close(data->fd_in[0]);
		dup2(data->fd_in[1], STDIN_FILENO);
		data->fd_in[0] = STDIN_FILENO;
	}
}