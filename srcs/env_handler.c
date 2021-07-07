#include "minishell.h"

char	*key_not_found(char *str, int start, int end)
{
	char	*before_variable;
	char	*new_str;

	before_variable = ft_substr(str, 0, start);
	new_str = ft_strjoin(before_variable, str + end);
	if (before_variable)
		free(before_variable);
	return (new_str);
}

char 	*key_found(char *value, char *str, int start, int end)
{
	char 	*new_str;
	char 	*merge_str;

	new_str = ft_substr(str, 0, start);
	merge_str = ft_strjoin(new_str, value);
	if (new_str)
		free(new_str);
	new_str = ft_strjoin(merge_str, str + end);
	if (merge_str)
		free(merge_str);
	return (new_str);
}

char	*env_handler(char *str, int *i, t_data *data)
{
	char	*env_key;
	char	*new_str;
	int		start;
	char	*value;

	start = *i;
	(*i)++;
	while (str[*i] == '_' || ft_isalnum(str[*i]) || str[*i] == '?')
		(*i)++;
	env_key = ft_substr(str, start + 1, *i - start - 1);
	if (!ft_strncmp(env_key, "?", ft_strlen(env_key)))
		value = ft_itoa(data->exit_status);
	else
		value = getenv(env_key);
	if (!value)
	{
		new_str = key_not_found(str, start, *i);
		*i = start;
	}
	else
		new_str = key_found(value, str, start, *i);
	return (new_str);
}
