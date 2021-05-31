#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		syn_error;
	char	*str;
	char	*cmd;
	char	***cmd_lines;
	int 	cmd_count;
	char	*arg;
	int		flag;
	char	**env;
	int		fd;
	int 	fd2;
}				t_data;

void	parsing(t_data *data);
void	execute_cmd(char **cmd_line);
void	error_handler(char *str);
int		check_syntax(char *str);
void	spec_sym_handler(t_data *data);
void	split_cmd(t_data *data);
void	make_string(char **str, char c);
char	*env_handler(char *str, int *i, char **env);
#endif

