#include "minishell.h"

void	execute_cmd(char **cmd_line, t_data *data)
{
	int	i;
	(void)data;

//	ft_putstr_fd("fd output = ", 1);
//	ft_putnbr_fd(data->fd_out, 1);
//	ft_putstr_fd(" ", 1);
//	ft_putstr_fd("fd input = ", 1);
//	ft_putnbr_fd(data->fd_in, 1);
//	ft_putstr_fd(" ", 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = 1;
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = 0;
	if (data->fd_heredoc)
	{
//		ft_putstr_fd("heredoc!! = \n", 1);
		ft_putstr_fd(data->heredoc, 1);
	}
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen(cmd_line[0])))
	{
		echo(cmd_line);
//		printf("cmd = %s ", cmd_line[0]);
//		i = 1;
//		while (cmd_line[i])
//		{
//			printf("| %d arg = |%s| ", i, cmd_line[i]);
//			i++;
//		}
//		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen(cmd_line[0])))
	{
		cd(cmd_line);
//		printf("cmd = %s ", cmd_line[0]);
//		i = 1;
//		while (cmd_line[i])
//		{
//			printf("| %d arg = %s ", i, cmd_line[i]);
//			i++;
//		}
//		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen(cmd_line[0])))
	{
		pwd();
//		printf("cmd = %s ", cmd_line[0]);
//		i = 1;
//		while (cmd_line[i])
//		{
//			printf("| %d arg = %s ", i, cmd_line[i]);
//			i++;
//		}
//		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "export", ft_strlen(cmd_line[0])))
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
	else if (!ft_strncmp(cmd_line[0], "unset", ft_strlen(cmd_line[0])))
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
	else if (!ft_strncmp(cmd_line[0], "env", ft_strlen(cmd_line[0])))
	{
		env(data);
//		printf("cmd = %s ", cmd_line[0]);
//		i = 1;
//		while (cmd_line[i])
//		{
//			printf("| %d arg = %s ", i, cmd_line[i]);
//			i++;
//		}
//		printf("\n");
	}
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen(cmd_line[0])))
		exit(data->exit_status);
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd_line[0], 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd("command not found", 1);
		data->exit_status = 127;
	}
}