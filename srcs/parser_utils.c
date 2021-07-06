#include "minishell.h"

char *readline_history(char *prompt, char *line_read)
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