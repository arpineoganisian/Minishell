#include "minishell.h"

int		redirect(char *str, int i, t_data *data)
{
	int		tmp;
	char	*filename;

	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] != ' ' && str[i] != '|' && str[i])
		i++;
	filename = ft_substr(str, tmp, i - tmp - 1);
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
	while (str[i] != ' ' && str[i] != '|' && str[i])
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

int		redir_handler(char *str, int i, t_data *data, int check_fd)
{
	if (check_fd)
		close(data->fd);
	i++;
	if (str[i] != '>')
	{
		if (redirect(str, i + 1, data))
			return (1);
	}
	else
		if (app_redirect(str, i + 1, data))
			return (1);
	return (0);
}

char	*remove_redirect(char *str, int *i)
{
	char	*new_str;
	char	*first_part;
	int 	start;

	start = *i;
	(*i)++;
	if (str[*i] == '>')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] != ' ')
		(*i)++;
	first_part = ft_substr(str, 0, start);
	new_str = ft_strjoin(first_part, str + *i + 1);
	free(first_part);
	free(str);
	return (str);
}