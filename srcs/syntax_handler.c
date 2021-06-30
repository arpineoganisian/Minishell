#include "minishell.h"

int	check_syntax(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && (str[i - 1] < 0 || str[i + 1] == 0 || str[i + 1]
		== '|'))
		{
			error_handler("syntax error near unexpected token `|'");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}