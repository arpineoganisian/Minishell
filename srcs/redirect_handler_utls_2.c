#include "minishell.h"

int	ctrl_d_heredoc(char *tmp)
{
	ft_putstr_fd("\e[1F\e[3G", 1);
	exit_status = 1;
	if (tmp && *tmp)
		free(tmp);
	return (0);
}

int	heredoc_read(t_data *data, char *word)
{
	int		do_read;
	char	*tmp;

	tmp = ft_strdup("");
	data->heredoc = readline("> ");
	if (!data->heredoc)
		return (ctrl_d_heredoc(tmp));
	do_read = ft_strncmp(word, data->heredoc, ft_strlen(word));
	data->heredoc = string_join(data->heredoc, "\n");
	while (do_read)
	{
		data->heredoc = string_join(data->heredoc, tmp);
		if (tmp && *tmp)
			free(tmp);
		tmp = readline("> ");
		if (!tmp)
			return (ctrl_d_heredoc(tmp));
		do_read = ft_strncmp(word, tmp, ft_strlen(word));
		tmp = string_join(tmp, "\n");
	}
	if (tmp && *tmp)
		free(tmp);
	return (0);
}
