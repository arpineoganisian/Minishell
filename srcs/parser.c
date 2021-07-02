#include "minishell.h"

void	parsing(t_data *data)
{
	if (check_syntax(data->str) == 1)
		error_handler("syntax error near unexpected token `|'");
	else
		split_cmd(data);
}

/* 1 проверить синтакс (1 символ, не закрытые кавычки)
 * 2 разделить на ;
 * 3 раскрыть кавычки
 */