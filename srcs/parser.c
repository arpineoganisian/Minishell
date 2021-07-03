#include "minishell.h"

void	parsing(t_data *data)
{
	int syntax_error;

	syntax_error = check_syntax(data->str);
	if (syntax_error == 1)
		error_handler("syntax error near unexpected token `|'");
	else if (syntax_error == 2)
		error_handler("syntax error near unexpected token `>'");
	else if (syntax_error == 3)
		error_handler("syntax error near unexpected token `newline'");
	else if (syntax_error == 4)
		error_handler("syntax error near unexpected token `>>'");
	else if (syntax_error == 5)
		error_handler("syntax error near unexpected token `<'");
	else if (syntax_error == 6)
		error_handler("syntax error near unexpected token `<<'");
	else
		split_cmd(data);
}
