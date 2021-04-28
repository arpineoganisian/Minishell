#include "minishell.h"

void	read_stdin(char *buf)
{
	read(0, buf, 1024);
}

void	checking_command(char *cmd, t_parsing_data *parsing_data)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		parsing_data->cmd = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		parsing_data->cmd = ft_strdup(cmd);
	else
		write(0, "minishell: command not found\n",
			  ft_strlen("minishell: command not found\n"));
}

void	parse_command(char *buf, t_parsing_data *parsing_data)
{
	int		i;
	char	cmd[1024];

	i = 0;
	while ((buf[i] != ' ' && buf[i] != '\0' && buf[i] != '\n') || i < 1024)
	{
		cmd[i] = buf[i];
		i++;
	}
	cmd[i] = '\0';
	checking_command(cmd, parsing_data);
}

void	parsing(char *buf, t_parsing_data *parsing_data)
{
	parse_command(buf, parsing_data);
}

void	reading_parsing(char *buf, t_parsing_data *parsing_data)
{
	read_stdin(buf);
	parsing(buf, parsing_data);
}