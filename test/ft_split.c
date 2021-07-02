#include "../libft/libft.h"
#include <stdio.h>
#include "../inc/minishell.h"

int		redirect(char *str, int i, t_data *data)
{
	int		tmp;
	char	*filename;

	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] != ' ' && str[i])
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

void	*remove_redirect(char **str, int i)
{
	char	*new_str;
	char	*first_part;
	int 	start;

	start = i;
	if (*str[i] == '>')
		(i)++;
	while (*str[i] == ' ')
		(i)++;
	while (*str[i] != ' ' && *str[i])
		i++;
	first_part = ft_substr(*str, 0, start);
	new_str = ft_strjoin(first_part, *str + i);
	free(first_part);
	*str = ft_strdup(new_str);
}

int		redirect_handler(char **str, int i, t_data *data, int check_fd)
{
	if (check_fd)
		close(data->fd);
	skip_other(*str, &i);
	if (*str[i] == '>' && *str[i + 1] != '>')
	{
		if (redirect(*str, i + 1, data))
			return (1);
	}
	else if (*str[i] == '>' && str[i + 1] *== '>')
	if (app_redirect(*str, i + 1, data))
		return (1);
	remove_redirect(str, i + 1);
	return (0);
}

int	main(void)
{
	char 	*str;
	char	**tmp;
	int i;

	//str = ft_strdup("\"foo | bar\" | pwd one |ls two three \'four five |"
	//		"\"hello world\" \'okay | \' not okay");
	str = ft_strdup(" \'hello world | \'fo ba\' \"|\" yes\' now ");
	tmp = split_line(str);
	i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	printf("%s\n", tmp[i]);
	return (0);
}