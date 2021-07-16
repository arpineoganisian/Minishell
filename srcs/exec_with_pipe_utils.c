#include "minishell.h"

void	malloc_things(t_data *data, pid_t **pid, int tokens_count)
{
	int	i;

	*pid = malloc(sizeof(pid_t) * tokens_count);
	data->fd = (int **) malloc(sizeof(int *) * (tokens_count + 1));
	if (!data->fd)
		error_handler("malloc failed", 1);
	i = 0;
	while (i <= tokens_count)
	{
		data->fd[i] = (int *) malloc(sizeof(int) * 2);
		if (!data->fd[i])
			error_handler("malloc failed", 1);
		i++;
	}
}

void	free_things(t_data *data, pid_t *pid, int tokens_count)
{
	free(pid);
	while (tokens_count >= 0)
		free(data->fd[tokens_count--]);
	free(data->fd);
}
