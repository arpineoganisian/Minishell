#include "minishell.h"

char	*readline_history(char *prompt, char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

char	*string_join(char *str1, char *str2)
{
	char	*str;
	int		i;

	str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*str1)
		*(str + i++) = *str1++;
	while (*str2)
		*(str + i++) = *str2++;
	*(str + i) = '\0';
	if (*str1)
		free(str1);
	return (str);
}

char **copy_envp(char **envp)
{
	char	**envp_copy;
	int		i;

	i = 0;
	envp_copy = malloc(sizeof(char*) * (strings_counter(envp) + 1));
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}