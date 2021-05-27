#include "minishell.h"

void	execute_cmd(t_parsing_data *parsing_data)
{
	if (!ft_strncmp(parsing_data->cmd, "echo", ft_strlen("echo")))
	{
		if (parsing_data->arg[0] != '\0')
			write(0, parsing_data->arg, ft_strlen(parsing_data->arg));
		if (parsing_data->flag != 1)
			write(0, "\n", 1);
	}
	else if (!ft_strncmp(parsing_data->cmd, "cd", ft_strlen("cd")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "pwd", ft_strlen("pwd")))
		write(0, "pwd\n", ft_strlen("pwd\n"));
	else if (!ft_strncmp(parsing_data->cmd, "export", ft_strlen("export")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "unset", ft_strlen("unset")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "env", ft_strlen("env")))
		;
	else if (!ft_strncmp(parsing_data->cmd, "exit", ft_strlen("exit")))
		exit(0);
	else
	{
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(parsing_data->cmd, 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd("command not found", 0);
	}
}