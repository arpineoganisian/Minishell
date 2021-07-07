#include "minishell.h"

int pwd()
{
	 char	*pwd;
	 int	fd;

	 fd = 1;
	 pwd = getcwd(NULL, 0);
	 if (!pwd)
	 {
	 	ft_putendl_fd(strerror(errno), 2);
		 return 1;
	 }
	 else
	 {
	 	ft_putendl_fd(pwd, fd);
	 	free(pwd);
	 }
	return 0;
}