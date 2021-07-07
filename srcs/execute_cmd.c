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
	if (!ft_strncmp(cmd_line[0], "echo", ft_strlen("echo")))
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
	else if (!ft_strncmp(cmd_line[0], "cd", ft_strlen("cd")))
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
	else if (!ft_strncmp(cmd_line[0], "pwd", ft_strlen("pwd")))
	{
		//TODO:
		// Оригинальный bash при команде "pwd+еще какая-то шняга без пробела" (напр: pwd000)
		// говорит, что команда не найдена
		// Наш работает, потому что strncmp все равно возвращает 0 в таком случае
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
	else if (!ft_strncmp(cmd_line[0], "exit", ft_strlen("exit")))
		exit(0);
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd_line[0], 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd("command not found", 1);
	}
}