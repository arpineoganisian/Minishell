#include "minishell.h"

void	parsing_start(t_data *data)
{
	char	**tmp;
	int		pipes_count;
	int		tokens_count;

	pipes_count = command_line_count(data->line_read);
	tokens_count = pipes_count + 1;
	tmp = split_by_pipe(data->line_read);
	if (pipes_count > 0)
		exec_cmd_line_with_pipes(data, tmp, tokens_count);
	else
	{
		split_and_exec(data, tmp[0]);
		reset_fd_to_default(data);
	}
}

void	parsing(t_data *data)
{
	int	syntax_error;

	syntax_error = check_syntax(data->line_read);
	if (syntax_error == 1)
		error_handler("syntax error near unexpected token `|'", 258);
	else if (syntax_error == 2)
		error_handler("syntax error near unexpected token `>'", 258);
	else if (syntax_error == 3)
		error_handler("syntax error near unexpected token `newline'", 258);
	else if (syntax_error == 4)
		error_handler("syntax error near unexpected token `>>'", 258);
	else if (syntax_error == 5)
		error_handler("syntax error near unexpected token `<'", 258);
	else if (syntax_error == 6)
		error_handler("syntax error near unexpected token `<<'", 258);
	else
		parsing_start(data);
}
