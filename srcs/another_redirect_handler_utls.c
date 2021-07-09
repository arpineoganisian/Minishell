#include "minishell.h"

int	ctrl_d_heredoc()
{
	ft_putstr_fd("\e[1F\e[3G", 1);
	exit_status = 1;
	return (0);
}

void ctrl_c_heredoc(int sig)
{
	(void)sig;
	exit_status = 999;
}

int heredoc_read(t_data *data, char *word)
{
	int		do_read;
	int		exit_status_tmp;
	char	*tmp;

	exit_status_tmp = exit_status;
	signal(SIGINT, ctrl_c_heredoc);
	data->heredoc = readline("> ");
	if (!data->heredoc)
		return (ctrl_d_heredoc());
	do_read = ft_strncmp(word, data->heredoc, ft_strlen(word));
	data->heredoc = string_join(data->heredoc, "\n");
	tmp = ft_strdup("");
	while (do_read && exit_status != 999)
	{
		data->heredoc = string_join(data->heredoc, tmp);
		if (tmp && *tmp)
			free(tmp);
		tmp = readline("> ");
		if (!tmp)
			return (ctrl_d_heredoc());
		do_read = ft_strncmp(word, tmp, ft_strlen(word));
		tmp = string_join(tmp, "\n");
	}
	if (tmp && *tmp)
		free(tmp);
	return (0);
}
