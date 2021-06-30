#include "minishell.h"

void	execute_cmd(char **cmd_line, t_data *data)
{
<<<<<<< HEAD
<<<<<<< HEAD
	if (!ft_strncmp(parsing_data->cmd, "echo ", ft_strlen("5")))
		// write(0, "echo\n", ft_strlen("echo\n"));
		echo(parsing_data);
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
=======
=======
>>>>>>> master
	int	i;

	printf("fd = %d ", data->fd);
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen("echo")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen("cd")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen("pwd")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "export", ft_strlen("export")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "unset", ft_strlen("unset")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "env", ft_strlen("env")))
	{
		printf("cmd = %s ", cmd_line[0]);
		i = 1;
		while (cmd_line[i])
		{
			printf("| %d arg = %s ", i, cmd_line[i]);
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen("exit")))
<<<<<<< HEAD
>>>>>>> Misha
=======
=======
	if (!ft_strncmp(parsing_data->cmd, "echo ", ft_strlen("5")))
		// write(0, "echo\n", ft_strlen("echo\n"));
		echo(parsing_data);
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
>>>>>>> 563447a5929771f5da3d936076105b0c6d828cb7
>>>>>>> master
		exit(0);
	else
	{
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(cmd_line[0], 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd("command not found", 0);
	}
}