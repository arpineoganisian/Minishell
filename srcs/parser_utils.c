#include "minishell.h"

char *readline_history(char *prompt, char *line_read)
{
	if (line_read)
	{
		free (line_read);
		line_read = NULL;
	}
	line_read = readline (prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}