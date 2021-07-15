#include "minishell.h"

int	get_out_from_child(char *tmp, char *heredoc, int *fd)
{
	if (tmp && *tmp)
		free(tmp);
	close(fd[0]);
	write(fd[1], heredoc, ft_strlen(heredoc) + 1);
	close(fd[1]);
	ft_putstr_fd("\e[1A\e[2C", STDOUT_FILENO);
	exit(0);
}

void	ctrl_c_herdoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\e[1F\e[1G\e[0K", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

void	read_heredoc_from_child(int *fd, char *word)
{
	int		do_read;
	char	*tmp;
	char	*heredoc;

	tmp = ft_strdup("");
	heredoc = readline("> ");
	if (!heredoc)
		get_out_from_child(tmp, heredoc, fd);
	else
	{
		do_read = ft_strncmp(word, heredoc, ft_strlen(word));
		heredoc = string_join(heredoc, "\n");
		while (do_read)
		{
			heredoc = string_join(heredoc, tmp);
			if (tmp && *tmp)
				free(tmp);
			tmp = readline("> ");
			if (!tmp)
				get_out_from_child(tmp, heredoc, fd);
			do_read = ft_strncmp(word, tmp, ft_strlen(word));
			tmp = string_join(tmp, "\n");
		}
		get_out_from_child(tmp, heredoc, fd);
	}
}

int	heredoc_read(t_data *data, char *word)
{
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
		return (1);
	data->pid_child = fork();
	if (data->pid_child == -1)
		return (1);
	if (data->pid_child == 0)
	{
		signal(SIGINT, ctrl_c_herdoc);
		read_heredoc_from_child(fd, word);
	}
	else
	{
		wait(&status);
		signal(SIGINT, ctrl_c);
		exit_status = WEXITSTATUS(status);
		close(fd[1]);
		data->fd_in[1] = dup(STDIN_FILENO);
		data->fd_in[0] = fd[0];
		dup2(data->fd_in[0], STDIN_FILENO);
	}
	return (0);
}
