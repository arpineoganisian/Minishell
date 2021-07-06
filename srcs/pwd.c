#include "minishell.h"

void pwd()
{
	 char *pwd;
	 int fd;

	 fd = 1;
	 pwd = getcwd(NULL, 0);
	 if(!pwd)
	 {
		 //ошибка
	 }
	 else
	 {
	 	ft_putendl_fd(pwd, fd);
	 	free(pwd);
	 }
}