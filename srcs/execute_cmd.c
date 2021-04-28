#include "minishell.h"

void	execute_cmd(t_parsing_data *parsing_data)
{
	if (!ft_strncmp(parsing_data->cmd, "echo", ft_strlen("echo")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "cd", ft_strlen("cd")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "pwd", ft_strlen("pwd")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "export", ft_strlen("export")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "unset", ft_strlen("unset")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "env", ft_strlen("env")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "exit", ft_strlen("exit")))
		exit(0);
	else
		write(0, "minishell: command not found\n",
			  ft_strlen("minishell: command not found\n"));
}