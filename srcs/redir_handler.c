#include "minishell.h"

int		redirect(char *str, int i, t_data *data)
{
	int		tmp;
	char	*filename;

	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] != ' ' && str[i])
		i++;
	filename = ft_substr(str, tmp, i - tmp);
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
	int		tmp;
	char	*filename;

	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] != ' ' && str[i])
		i++;
	filename = ft_substr(str, tmp, i - tmp - 1);
	data->fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(filename);
	if (data->fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

void	skip_other(char *str, int *i)
{
	int	tmp;

	while (str[*i] != '>' && str[*i])
	{
		if (str[*i] == '\'')
		{
			tmp = 0;
			(*i)++;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
			if (str[*i] != '\'')
				*i = tmp;
		}
		if (str[*i] == '\"')
		{
			tmp = 0;
			(*i)++;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
			if (str[*i] != '\"')
				*i = tmp;
		}
		if (str[*i])
			(*i)++;
	}
}

void	remove_redirect(char **str, int i)
{
	char	*new_str;
	char	*first_part;
	int 	start;

	start = i;
	while ((*str)[i] == '>')
		(i)++;
	while ((*str)[i] == ' ')
		(i)++;
	while ((*str)[i] != ' ' && (*str)[i])
		i++;
	first_part = ft_substr(*str, 0, start);
	new_str = ft_strjoin(first_part, *str + i);
	free(first_part);
	free(*str);
	*str = ft_strdup(new_str);
	free(new_str);
}

int		redirect_handler(char **str, t_data *data)
{
	int	fd_opened;
	int	i;

	fd_opened = 0;
	i = 0;
	while (str[i])
	{
		skip_other(*str, &i);
		if ((*str)[i] == '>' && (*str)[i + 1] != '>')
		{
			if (fd_opened)
				close(data->fd);
			fd_opened = 1;
			if (redirect(*str, i + 1, data))
				return (1);
			remove_redirect(str, i);
		}
		if ((*str)[i] == '>' && (*str)[i + 1] == '>')
		{
			if (fd_opened)
				close(data->fd);
			fd_opened = 1;
			if (app_redirect(*str, i + 1, data))
				return (1);
		}
		if(str[i])
			i++;
	}
	return (0);
}
