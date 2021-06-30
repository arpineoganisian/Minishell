#include "minishell.h"

void	execute_cmd(char **cmd_line, t_data *data)
{
	int	i;
	(void)data;

	//printf("fd = %d ", data->fd);
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
		exit(0);
	else
	{
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(cmd_line[0], 0);
		ft_putstr_fd(": ", 0);
		ft_putendl_fd("command not found", 0);
	}
}