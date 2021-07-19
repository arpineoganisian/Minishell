#include "minishell.h"

char	*ft_strnstr2(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	tmp;

	tmp = 0;
	if (needle[tmp] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		while (haystack[i + tmp] == needle[tmp] && (tmp + i) < len)
		{
			if (haystack[i + tmp] == '\0' && needle[tmp] == '\0')
				return ((char *)&haystack[i]);
			tmp++;
		}
		if (needle[tmp] == '\0')
			return ((char *)&haystack[i]);
		tmp = 0;
		i++;
	}
	return (NULL);
}


int	env_key_finder(char **envp, char *env_key)
{
	int		i;
	int		k;
	char	*current_key;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr2(envp[i], env_key, ft_strlen(env_key)))
		{
			k = 0;
			while (envp[i][k] != '=' && envp[i][k])
				k++;
			current_key = ft_substr(envp[i], 0, k);
			if (equal_str(env_key, current_key))
			{
				free(current_key);
				return (i);
			}
			free(current_key);
		}
		i++;
	}
	return (-1);
}

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

char	*key_found(char *env_str, char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;
	int		i;

	i = 0;
	while (env_str[i] != '=' && env_str[i])
		i++;
	env_value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i);
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

char	*make_env_key(char *str, int *i, int start)
{
	char	*env_key;

	while (str[*i] == '_' || ft_isalnum(str[*i]) || str[*i] == '?')
		(*i)++;
	env_key = ft_substr(str, start + 1, *i - start - 1);
	return (env_key);
}

char	*env_handler(char *str, int *i, char **envp)
{
	char	*env_key;
	char	*new_str;
	int		start;
	int		line_number;

	start = *i;
	(*i)++;
	if (ft_isdigit(str[*i]))
		new_str = positional_parameter(str, start, ++(*i));
	else
	{
		env_key = make_env_key(str, i, start);
		if (equal_str("?", env_key))
			new_str = exit_status_env(str, start, *i);
		else
		{
			line_number = env_key_finder(envp, env_key);
			if (line_number == -1)
				new_str = key_not_found(str, start, *i);
			else
				new_str = key_found(envp[line_number], str, start, *i);
		}
		free(env_key);
	}
	free(str);
	*i = start;
	return (new_str);
}
