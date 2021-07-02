#include "minishell.h"

char	*quotes_handler(char *str, int *i)
{
	char	*new_str;
	char	*in_quotes_part;
	char	*merge_parts;
	int		start;

	start = *i;
	new_str = ft_substr(str, 0, start);
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
	in_quotes_part = ft_substr(str, start + 1, *i - start - 1);
	merge_parts = ft_strjoin(new_str, in_quotes_part);
	free(new_str);
	free(in_quotes_part);
	new_str = ft_strjoin(merge_parts, str + *i + 1);
	free(merge_parts);
	free(str);
	*i -= 2;
	if (*i < 0)
		*i = 0;
	return (new_str);
}

char	*dquotes_handler(char *str, int *i, char **env)
{
	char	*new_str;
	char	*in_quotes_part;
	char	*merge_parts;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] != '\"' && str[*i])
	{
		if (str[*i] == '$')
			str = env_handler(str, &(*i), env);
		(*i)++;
	}
	new_str = ft_substr(str, 0, start);
	in_quotes_part = ft_substr(str, start + 1, *i - start - 1);
	merge_parts = ft_strjoin(new_str, in_quotes_part);
	free(new_str);
	free(in_quotes_part);
	new_str = ft_strjoin(merge_parts, str + *i + 1);
	free(merge_parts);
	free(str);
	*i -= 2;
	if (*i < 0)
		*i = 0;
	return (new_str);
}

int		closed_quotes(char *str, int i, char qs)
{
	i++;
	while (str[i])
	{
		if (str[i] == qs)
			return (1);
		i++;
	}
	return (0);
}

int		spec_sym_handler(char **str, t_data *data)
{
	int	i;
	int	check_fd;

	check_fd = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '>')
		{
			if (redir_handler(*str, i, data, check_fd))
				return (1);
			check_fd = 1;
			*str = remove_redirect(*str, &i);
		}
		if ((*str)[i] == '\'' && closed_quotes(*str, i, '\''))
			*str = quotes_handler(*str, &i);
		if ((*str)[i] == '\"' && closed_quotes(*str, i, '\"'))
			*str = dquotes_handler(*str, &i, data->env);
		if ((*str)[i] == '$')
			*str = env_handler(*str, &i, data->env);
		if ((*str)[i] && !((*str)[i] == '\"' && closed_quotes(*str, i, '\"'))
		&& !((*str)[i] == '\'' && closed_quotes(*str, i, '\''))
		&& (*str)[i] != '$')
			i++;
	}
	return (0);
}