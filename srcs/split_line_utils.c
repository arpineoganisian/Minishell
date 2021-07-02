#include "minishell.h"

int	closed_quotes_check(char *str, int i, char qs)
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

void 	copy_word(char *str, int *i, char **split_string, char s)
{
	int	count;

	count = 0;
	(*split_string)[count++] = str[(*i)++];
	while (str[*i] != s && str[*i])
		(*split_string)[count++] = str[(*i)++];
	(*split_string)[count++] = str[(*i)++];
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\"' && closed_quotes_check(str, *i, '\"'))
		{
			(*split_string)[count++] = str[(*i)++];
			while (str[*i] != '\"' && str[*i])
				(*split_string)[count++] = str[(*i)++];
			(*split_string)[count++] = str[(*i)++];
		}
		if (str[*i] == '\'' && closed_quotes_check(str, *i, '\''))
		{
			(*split_string)[count++] = str[(*i)++];
			while (str[*i] != '\'' && str[*i])
				(*split_string)[count++] = str[(*i)++];
			(*split_string)[count++] = str[(*i)++];
		}
		if (str[*i] != ' ')
			(*split_string)[count++] = str[(*i)++];
	}
	(*split_string)[count] = '\0';
}

void	copy_space_word(char *str, int *i, char **split_string)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes_check(str, *i, '\''))
		{
			(*split_string)[char_count++] = str[(*i)++];
			while (str[*i] != '\'' && str[*i])
				(*split_string)[char_count++] = str[(*i)++];
		}
		(*split_string)[char_count++] = str[(*i)++];
	}
	(*split_string)[char_count] = '\0';
}

int	char_count(char *str, int *i, char s)
{
	int	count;

	count = 0;
	(*i)++;
	count++;
	while (str[*i] != s && str[*i])
	{
		(*i)++;
		count++;
	}
	(*i)++;
	count++;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\"' && closed_quotes_check(str, *i, '\"'))
			count += char_count(str, i, '\"');
		if (str[*i] == '\'' && closed_quotes_check(str, *i, '\''))
			count += char_count(str, i, '\'');
		if (str[*i] != ' ')
		{
			(*i)++;
			count++;
		}
	}
	return (count);
}

int	not_qs_char_count(char *str, int *i)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes_check(str, *i, '\''))
		{
			(*i)++;
			char_count++;
			while (str[*i] != '\'' && str[*i])
			{
				(*i)++;
				char_count++;
			}
		}
		(*i)++;
		char_count++;
	}
	return (char_count);
}
