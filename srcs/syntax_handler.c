#include "minishell.h"

int	check_syntax(const char *str)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			tmp = i;
			while (str[i] == ' ')
				i--;
			if (str[i] < 0)
				error_handler("syntax error near unexpected token `|'");
			i = tmp;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|' || str[i] == '\0')
				error_handler("syntax error near unexpected token `|'");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}