#include "minishell.h"

char *positional_parameter(char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;

	if (str[end - 1] == '0')
	{
		env_value = ft_strdup("minishell");
		new_str = ft_substr(str, 0, start);
		merge_str = ft_strjoin(new_str, env_value);
		if (new_str)
			free(new_str);
		if (env_value)
			free(env_value);
		new_str = ft_strjoin(merge_str, str + end);
		if (merge_str)
			free(merge_str);
	}
	else
	{
		merge_str = ft_substr(str, 0, start);
		new_str = ft_strjoin(merge_str, str + end);
		if (merge_str)
			free(merge_str);
	}
	return (new_str);
}

char	*exit_status_env(char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;

	env_value = ft_itoa(exit_status);
	new_str = ft_substr(str, 0, start);
	merge_str = ft_strjoin(new_str, env_value);
	if (new_str)
		free(new_str);
	if (env_value)
		free(env_value);
	new_str = ft_strjoin(merge_str, str + end);
	if (merge_str)
		free(merge_str);
	return (new_str);
}