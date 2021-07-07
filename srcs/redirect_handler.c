#include "minishell.h"

int input_redirect(char *str, int i, t_data *data)
{
	char	*filename;
	char	*error;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	data->fd_in = open(filename, O_RDONLY, 0644);
	if (data->fd_in == -1)
	{
		error = ft_strjoin(filename, ": ");
		free(filename);
		error_handler(ft_strjoin(error, strerror(errno)), data, 1, 2);
		free(error);
		close(data->fd_in);
		data->fd_in = 0;
		return (1);
	}
	free(filename);
	return (0);
}

int output_redirect(char **str, int *i, t_data *data, int *fd_out_opened)
{
	int	error;

	error = 0;
	if ((*str)[*i] == '>')
	{
		if (*fd_out_opened)
			close(data->fd_out);
		*fd_out_opened = 1;
		if ((*str)[*i + 1] == '>')
			error = app_redirect(*str, *i + 2, data);
		else
			error = redirect(*str, *i + 1, data);
		remove_redirect(str, i, '>');
	}
	return (error);
}

int heredoc_redirect(char *str, int i, t_data *data)
{
	char	*word;
	char 	*tmp;
	int		do_read;

	while (str[i] == ' ')
		i++;
	word = make_filename(str, i, data);
	data->heredoc = readline(">");
	do_read = ft_strncmp(word, data->heredoc, ft_strlen(word));
	data->heredoc = string_join(data->heredoc, "\n");
	tmp = ft_strdup("");
	while (do_read)
	{
		data->heredoc = string_join(data->heredoc, tmp);
		if (tmp && *tmp)
			free(tmp);
		tmp = readline(">");
		do_read = ft_strncmp(word, tmp, ft_strlen(word));
		tmp = string_join(tmp, "\n");
	}
	if (tmp && *tmp)
		free(tmp);
	data->fd_heredoc = 1;
	free(word);
	return (0);
}

int	input_heredoc_redirect(char **str, int *i, t_data *data, int *fd_in_opened)
{
	int	error;

	error = 0;
	if ((*str)[*i] == '<')
	{
		if (*fd_in_opened)
			close(data->fd_in);
		*fd_in_opened = 1;
		if ((*str)[*i + 1] == '<')
			error = heredoc_redirect(*str, *i + 2, data);
		else
			error = input_redirect(*str, *i + 1, data);
		remove_redirect(str, i, '<');
	}
	return (error);
}

int	redirect_handler(char **str, t_data *data)
{
	int	fd_out_opened;
	int fd_in_opened;
	int	i;
	int	error;

	fd_out_opened = 0;
	fd_in_opened = 0;
	i = 0;
	while ((*str)[i])
	{
		skip_other(*str, &i);
		error = output_redirect(str, &i, data, &fd_out_opened);
		if (error)
			return (1);
		error = input_heredoc_redirect(str, &i, data, &fd_in_opened);
		if (error)
			return (1);
		if ((*str)[i] != '>' && (*str)[i])
			i++;
	}
	return (0);
}
