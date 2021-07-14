#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"

int	exit_status;

typedef struct s_data
{
	//вся введенная строка:
	char	*line_read;
	//массив строк - команды и аргументы:
	char	***cmd_lines;
	//тут храним фд вывода [0] - открытый файл [1] - копия STDOUT
	int		fd_out[2];
	//тут храним фд ввода
	int 	fd_in[2];
	//если был heredoc, то фд = 1
	int 	fd_heredoc;
	//если фд_хередок = 1, то тут input строка
	char	*heredoc;
	//переменные окружения из main()
	char	**envp;
}				t_data;

void	parsing(t_data *data);
void	execute_cmd(char **cmd_line, t_data *data);
void	error_handler(char *str, int exit_status);
int		check_syntax(char *str);
void	spec_sym_handler(char **str, t_data *data);
void	split_cmd(t_data *data);
char	*env_handler(char *str, int *i, char **envp);
int		closed_quotes(char *str, int i, char qs);
char	**split_line(char *str);
void	malloc_word(char *str, int *i, char **split_string, char s);
int		char_count(char *str, int *i, char s);
void	copy_space_word(char *str, int *i, char **split_string);
void 	copy_word(char *str, int *i, char **split_string, char s);
int		command_line_count(char *str);
void	line_char_count(char *str, int *i);
int		not_qs_char_count(char *str, int *i);
int		redirect_handler(char **str, t_data *data);
char	*dquotes_handler(char *str, int *i, t_data *data);
void	skip_other(char *str, int *i);
char	*make_filename(char *str, int i, t_data *data);
char	*readline_history(char *prompt, char *line_read);
void	remove_redirect(char **str, int *i, char c);
int 	app_redirect(char *str, int i, t_data *data);
int		redirect(char *str, int i, t_data *data);
char	*string_join(char *str1, char *str2);
int 	heredoc_read(t_data *data, char *word);
void	ctrl_c(int sig);

/*
** builtins
*/

int		echo(char **cmd_line);
int 	cd(char **cmd_line);
int		pwd();
int		export(char **cmd_line, t_data *data);
int		unset(char **cmd_line, t_data *data);
int		env(t_data *data);

int 	strings_counter(char **array);
void	execute_bin(char **cmd_line, t_data *data);
int		find_env_var(char *var, t_data *data);
#endif
