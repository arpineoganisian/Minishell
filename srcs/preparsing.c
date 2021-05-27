#include "minishell.h"

int	check_symbol(char *buf, int i)
{
	if (buf[0] == '|')
		error_handler("syntax error near unexpected token `|'");
	else if (buf[0] == ';')
		error_handler("syntax error near unexpected token `;'");
	else if (buf[i] == '|' && buf[i + 1] == '|')
		error_handler("syntax error near unexpected token `||'");
	else if (buf[i] == ';' && buf[i + 1] == ';')
		error_handler("syntax error near unexpected token `;;'");
	else if (buf[i] == ';' && buf[i + 1] == '|')
		error_handler("syntax error near unexpected token `;'");
	else if (buf[i] == '|' && buf[i + 1] == ';')
		error_handler("syntax error near unexpected token `|'");
	else if (buf[i] == '\\' && buf[i + 1] == '\n')
		error_handler("syntax error: missing symbol after `\\'");
	else return (0);
	return (1);
}

int	preparsing(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n')
	{
		if (check_symbol(buf, i) == 1)
			return (1);
		else if (buf[i] == '\"')
		{
			i++;
			while (buf[i] != '\n' && buf[i] != '\"')
				i++;
			if (buf[i] != '\"')
			{
				error_handler("syntax error: multiline commands are not "
							  "allowed");
				return (1);
			}
		}
		else if (buf[i] == '\'')
		{
			i++;
			while (buf[i] != '\n' && buf[i] != '\'')
				i++;
			if (buf[i] != '\'')
			{
				error_handler("syntax error: multiline commands are not "
							  "allowed");
				return (1);
			}
		}
		if (buf[i] != '\n')
			i++;
	}
	return (0);
}