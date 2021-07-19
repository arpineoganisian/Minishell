#include "minishell.h"

void	exec_cmd(char **cmd_line, t_data *data)
{
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen("echo")))
		echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen("cd")))
		cd(cmd_line, data, 0);
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen("pwd")))
		pwd();
	else if (!ft_strncmp(cmd_line[0], "export", ft_strlen("export")))
		export(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "unset", ft_strlen("unset")))
		unset(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "env", ft_strlen("env")))
		env(data);
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen("exit")))
		exit_minishell(cmd_line);
	else
		execute_bin(cmd_line, data);
	free_splited_arr(cmd_line);
}

void	exec_commands(t_data *data)
{
	dup2(data->fd_out[0], STDOUT_FILENO);
	dup2(data->fd_in[0], STDIN_FILENO);
	exec_cmd(data->cmd_lines, data);
}

void	split_and_exec(t_data *data, char *cmd_line)
{
	int	i;

	if (redirect_handler(&cmd_line, data))
		return ;
	data->cmd_lines = split_line(cmd_line);
	if (cmd_line)
	{
		free(cmd_line);
		cmd_line = NULL;
	}
	i = 0;
	while (data->cmd_lines[i])
		spec_sym_handler(&data->cmd_lines[i++], data);
	if (data->cmd_lines[0])
		exec_commands(data);
}
