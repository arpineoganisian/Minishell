#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			buf[1024];
	t_parsing_data	parsing_data;
	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		write(1, "\e[32mminishell> \e[0m", 20);
		reading_parsing(buf, &parsing_data);
		if (!ft_strncmp(parsing_data.str, "exit", ft_strlen("exit")))
			exit(0);
	}
}