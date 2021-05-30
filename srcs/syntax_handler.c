#include "minishell.h"

int	check_pipe_semicolon(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
		error_handler("syntax error near unexpected token `||'");
	else if (str[i] == ';' && str[i + 1] == ';')
		error_handler("syntax error near unexpected token `;;'");
	else if (str[i] == ';' && str[i + 1] == '|')
		error_handler("syntax error near unexpected token `;'");
	else if (str[i] == '|' && str[i + 1] == ';')
		error_handler("syntax error near unexpected token `|'");
	else if (str[i] == '\\' && str[i + 1] == '\n')
		error_handler("syntax error: missing symbol after `\\'");
	else
		return (0);
	return (1);
}

int	check_first_symbol(char *str)
{
	if (str[0] == ';')
		error_handler("syntax error near unexpected token `;'");
	else if (str[0] == '|')
		error_handler("syntax error near unexpected token `|'");
	else
		return (0);
	return (1);
}

int check_dquotes(char *str, int *i)
{
	(*i)++;
	while ((str[*i] && str[*i] != '\"') || (str[*i] == '\"'
												  && str[*i - 1] == '\\'))
		(*i)++;
	if (str[*i] != '\"')
	{
		error_handler("syntax error: multiline commands are not allowed");
		return (1);
	}
	return (0);
}

int check_quotes(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] != '\'')
	{
		error_handler("syntax error: multiline commands are not allowed");
		return (1);
	}
	return (0);
}

int	check_syntax(char *str)
{
	int	i;

	if (check_first_symbol(str))
		return (1);

	i = 0;
	while (str[i])
	{
		if (check_pipe_semicolon(str, i))
			return (1);
		else if (str[i] == '\"' && str[i - 1] != '\\' && check_dquotes(str, &i))
			return (1);
		else if (str[i] == '\'' && str[i - 1] != '\\' && check_quotes(str, &i))
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}