#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

<<<<<<< HEAD
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
void	execute_cmd(char **cmd_line, t_data *data);
void	error_handler(char *str);
int		check_syntax(char *str);
int 	spec_sym_handler(char **str, t_data *data);
void	split_cmd(t_data *data);
void	make_string(char **str, char c);
char	*env_handler(char *str, int *i, char **env);
int		check_first_symbol(char *str);
int		redir_handler(char *str, int i, t_data *data, int check_fd);
char	*remove_redirect(char *str, int *i);
=======
typedef struct	s_parsing_data
{
	char	*str;
	char	cmd[1024];
	int		option_n;
	int		single_quoted;
	int		double_quoted;
}				t_parsing_data;

void	reading_parsing(char *buf, t_parsing_data *parsing_data);
void	read_stdin(char *buf);
void	parsing(char *buf, t_parsing_data *parsing_data);
void	execute_cmd(t_parsing_data *parsing_data);
void	echo(t_parsing_data *parsing_data);
>>>>>>> 563447a5929771f5da3d936076105b0c6d828cb7
#endif

