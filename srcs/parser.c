#include "minishell.h"

void	parsing(t_data *data)
{
	if ((data->syn_error = check_syntax(data->str)))
		free(data->str);
	else
	{
		spec_sym_handler(data);
		split_cmd(data);
	}
}