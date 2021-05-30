#include "minishell.h"

char	*backslash_handler(char *str, int *i)
{
	char	*first_part;
	char	*new_str;

	first_part = ft_substr(str, 0, *i);
	new_str = ft_strjoin(first_part, str + *i + 1);
	free(first_part);
	free(str);
	return (new_str);
}

char	*quotes_handler(char *str, int *i)
{
	char	*new_str;
	char	*in_quotes_part;
	char	*merge_parts;
	int		start;

	start = *i;
	new_str = ft_substr(str, 0, start);
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	in_quotes_part = ft_substr(str, start + 1, *i - start - 1);
	merge_parts = ft_strjoin(new_str, in_quotes_part);
	free(new_str);
	free(in_quotes_part);
	new_str = ft_strjoin(merge_parts, str + *i + 1);
	free(merge_parts);
	free(str);
	return (new_str);
}

char	*dquotes_handler(char *str, int *i)
{
	char	*new_str;
	char	*in_quotes_part;
	char	*merge_parts;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] != '\"')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '\\' ||
		str[*i + 1] == '$'))
			str = backslash_handler(str, i);
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
	return (new_str);
}

void	spec_sym_handler(t_data *data)
{
	int	i;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '\'')
			data->str = quotes_handler(data->str, &i);
		if (data->str[i] == '\"')
			data->str = dquotes_handler(data->str, &i);
		if (data->str[i] == '\\')
			data->str = backslash_handler(data->str, &i);
		if (data->str[i] == '$')
			data->str = env_handler(data->str, &i, data->env);
		if (data->str[i])
			i++;
	}
}