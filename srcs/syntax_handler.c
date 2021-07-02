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
			tmp = i + 1;
			if (i > 0)
				i--;
			while (str[i] == ' ' && i > 0)
				i--;
			if (str[i] == ' ' || str[i] == '|')
				return (1);
			i = tmp;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|' || str[i] == '\0')
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
