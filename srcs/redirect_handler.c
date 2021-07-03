#include "minishell.h"

int	redirect(char *str, int i, t_data *data)
{
	char	*filename;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	data->fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(filename);
	if (data->fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int 	app_redirect(char *str, int i, t_data *data)
{
	char	*filename;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i, data);
	data->fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(filename);
	if (data->fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

void	remove_redirect(char **str, int *i)
{
	char	*new_str;
	char	*first_part;
	int		start;

	start = *i;
	while ((*str)[*i] == '>')
		(*i)++;
	while ((*str)[*i] == ' ')
		(*i)++;
	if ((*str)[*i] == '\"' && closed_quotes(*str, *i, '\"'))
		while ((*str)[++(*i)] != '\"')
			;
	else if ((*str)[*i] == '\'' && closed_quotes(*str, *i, '\''))
		while ((*str)[++(*i)] != '\'')
			;
	else
		while ((*str)[++(*i)] != ' ' && (*str)[*i])
			;
	first_part = ft_substr(*str, 0, start);
	new_str = ft_strjoin(first_part, *str + *i + 1);
	free(first_part);
	free(*str);
	*str = ft_strdup(new_str);
	free(new_str);
	*i = start;
}

int	redirect_handler(char **str, t_data *data)
{
	int	fd_opened;
	int	i;
	int	error;

	fd_opened = 0;
	i = -1;
	while ((*str)[++i])
	{
		skip_other(*str, &i);
		if ((*str)[i] == '>')
		{
			if (fd_opened)
				close(data->fd);
			fd_opened = 1;
			if ((*str)[i + 1] == '>')
				error = app_redirect(*str, i + 2, data);
			else
				error = redirect(*str, i + 1, data);
			if (error)
				return (1);
			remove_redirect(str, &i);
		}
	}
	return (0);
}
