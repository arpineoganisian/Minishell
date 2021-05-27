#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_parsing_data
{
	int		syn_error;
	char	*cmd;
	char	*arg;
	int		flag;
}		t_parsing_data;

void	reading_parsing(char *buf, t_parsing_data *parsing_data);
void	read_stdin(char *buf);
void	parsing(char *buf, t_parsing_data *parsing_data);
void	execute_cmd(t_parsing_data *parsing_data);
void	error_handler(char *str);
int 	preparsing(char *buf);
char	*spec_sym_handler(char *str);
#endif

