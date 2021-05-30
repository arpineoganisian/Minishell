#include "minishell.h"

char	*make_string(char *str, char c)
{
	char	*tmp;
	tmp = ft_calloc(ft_strlen(str) + 2, sizeof (char));
	ft_memcpy(tmp, str, ft_strlen(str));
	tmp[ft_strlen(tmp)] = c;
	if (str)
		free(str);
	return (tmp);
}

