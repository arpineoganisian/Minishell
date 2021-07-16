#include "minishell.h"

void	exec_cmd(char **cmd_line, t_data *data)
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
		exit_minishell();
	else
		execute_bin(cmd_line, data);
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
		free(cmd_line);
	i = 0;
	while (data->cmd_lines[i])
		spec_sym_handler(&data->cmd_lines[i++], data);
	exec_commands(data);
}
