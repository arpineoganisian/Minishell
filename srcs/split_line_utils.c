#include "minishell.h"

void 	copy_word(char *str, int *i, char **split_string, char s)
{
	int char_count;

	(*i)++;
	char_count = 0;
	while (str[*i] != s && str[*i])
	{
		(*split_string)[char_count] = str[*i];
		char_count++;
		(*i)++;
	}
	(*split_string)[char_count] = '\0';
	(*i)++;
}

void	copy_space_word(char *str, int *i, char **split_string)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != ' ' && str[*i])
	{
		(*split_string)[char_count] = str[*i];
		char_count++;
		(*i)++;
	}
	(*split_string)[char_count] = '\0';
}

int		closed_quotes_check(char *str, int i, char qs)
{
	i++;
	while (str[i])
	{
		if (str[i] == qs)
			return (1);
		i++;
	}
	return (0);
}

int		char_count(char *str, int *i, char s)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != s && str[*i])
	{
		(*i)++;
		char_count++;
	}
	return (char_count);
}

void	malloc_word(char *str, int *i, char **split_string, char s)
{
	(*i)++;
	*split_string = (char *)malloc(sizeof(char) *
								   (char_count(str, i, s) + 1));
	(*i)++;
}