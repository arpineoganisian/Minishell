#include "minishell.h"

int pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		//todo использовать еррор хегдлер
		ft_putendl_fd(strerror(errno), 2);
		return 1;
	}
	else
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
	 	free(pwd);
	}
	return 0;
}