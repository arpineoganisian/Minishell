#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_parsing_data
{
	char *str;
	char *cmd;
}		t_parsing_data;

void	reading_parsing(char *buf, t_parsing_data *parsing_data);
void	read_stdin(char *buf);
void	parsing(char *buf, t_parsing_data *parsing_data);
#endif

