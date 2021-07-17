#include "minishell.h"

void	reset_fd_to_default(t_data *data)
{
	dup2(data->fd_out[1], STDOUT_FILENO);
	dup2(data->fd_in[1], STDIN_FILENO);
	data->fd_out[0] = STDOUT_FILENO;
	data->fd_in[0] = STDIN_FILENO;
}

char	*readline_history(char *prompt, char *line_read, t_data *data)
{
	if (line_read && *line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	tcgetattr(STDOUT_FILENO, &data->config);
	data->config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
	line_read = readline(prompt);
	data->config.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &data->config);
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

char	**copy_envp(char **envp)
{
	char	**envp_copy;
	int		i;

	i = 0;
	envp_copy = malloc(sizeof(char *) * (strings_counter(envp) + 1));
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

void	make_string(char **str, char c)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(*str) + 2, sizeof (char));
	ft_memcpy(tmp, *str, ft_strlen(*str));
	tmp[ft_strlen(tmp)] = c;
	if (*str)
		free(*str);
	*str = tmp;
}
