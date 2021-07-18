#include "minishell.h"

int	get_out_from_child(char *tmp, char *heredoc, int *fd, t_data *data)
{
	if (tmp && *tmp)
		free(tmp);
	data->config.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	close(fd[0]);
	write(fd[1], heredoc, ft_strlen(heredoc) + 1);
	close(fd[1]);
	ft_putstr_fd("\e[1A\e[2C", STDOUT_FILENO);
	exit(0);
}

void	read_heredoc_from_child(int *fd, char *word, t_data *data)
{
	int		do_read;
	char	*tmp;
	char	*heredoc;

	tmp = ft_strdup("");
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	heredoc = readline("> ");
	if (!heredoc)
		get_out_from_child(tmp, heredoc, fd, data);
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
				get_out_from_child(tmp, heredoc, fd, data);
			do_read = ft_strncmp(word, tmp, ft_strlen(word));
			tmp = string_join(tmp, "\n");
		}
		get_out_from_child(tmp, heredoc, fd, data);
	}
}

int	heredoc_read(t_data *data, char *word)
{
	int	fd[2];
	int	status;
	pid_t pid_child;

	if (pipe(fd) == -1)
		return (1);
	pid_child = fork();
	signal(SIGQUIT, SIG_IGN);
	if (pid_child == -1)
		return (1);
	if (pid_child == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_heredoc_from_child(fd, word, data);
	}
	else
	{
		wait(&status);
		exit_status = WEXITSTATUS(status);
		signal(SIGINT, ctrl_c);
		close(fd[1]);
		close(data->fd_in[0]);
		data->fd_in[0] = fd[0];
	}
	return (0);
}

void	skip_filename(char *str, int *i)
{
	if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;;
	}
	else if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	else
	{
		while (str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i])
			(*i)++;
		(*i)--;
	}
}
