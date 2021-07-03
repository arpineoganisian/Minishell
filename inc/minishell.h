#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		syn_error;
	//вся введенная строка:
	char	*str;
	char	*cmd;
	//массив строк - команды и аргументы:
	char	***cmd_lines;
	int 	cmd_count;
	char	*arg;
	int		flag;
	//переменные окружения:
	char	**env;
	//тут храним фд вывода
	int		fd;
	int 	fd2;
}				t_data;

void	parsing(t_data *data);
void	execute_cmd(char **cmd_line, t_data *data);
void	error_handler(char *str);
int		check_syntax(char *str);
void 	spec_sym_handler(char **str, t_data *data);
void	split_cmd(t_data *data);
void	make_string(char **str, char c);
char	*env_handler(char *str, int *i, char **env);
int		closed_quotes(char *str, int i, char qs);
char	**split_line(char *str);
void	malloc_word(char *str, int *i, char **split_string, char s);
int		char_count(char *str, int *i, char s);
void	copy_space_word(char *str, int *i, char **split_string);
void 	copy_word(char *str, int *i, char **split_string, char s);
int		command_line_count(char *str);
void	line_char_count(char *str, int *i);
void    echo(char **cmd_line);
int 	strings_counter(char **array);
int		not_qs_char_count(char *str, int *i);
int		redirect_handler(char **str, t_data *data);
char	*dquotes_handler(char *str, int *i, char **env);
void	skip_other(char *str, int *i);
char	*make_filename(char *str, int i, t_data *data);
#endif

