#include "../libft/libft.h"
#include <stdio.h>

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

void 	copy_word(char *str, int *i, char **split_string, char s)
{
	int char_count;

	char_count = 0;
	(*split_string)[char_count++] = str[(*i)++];
	while (str[*i] != s && str[*i])
		(*split_string)[char_count++] = str[(*i)++];
	while(str[*i] != ' ' && str[*i])
		(*split_string)[char_count++] = str[(*i)++];
	(*split_string)[char_count] = '\0';
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

int		char_count(char *str, int *i, char s)
{
	int	char_count;

	char_count = 0;
	while (str[*i] != s && str[*i])
	{
		(*i)++;
		char_count++;
	}
	while (str[*i] != ' ' && str[*i])
	{
		(*i)++;
		char_count++;
	}
	return (char_count);
}

int		not_qs_char_count(char *str, int *i)
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

void	malloc_word(char *str, int *i, char **split_string, char s)
{
	(*i)++;
	*split_string = (char *)malloc(sizeof(char) *
			(char_count(str, i, s) + 1));
	if (str[*i] == s)
		(*i)++;
}

void	*split_words_malloc(char **split_string, char *str)
{
	int	i;
	int	words_count;

	words_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes_check(str, i, '\''))
			malloc_word(str, &i, &split_string[words_count++], '\'');
		if (str[i] == '\"' && closed_quotes_check(str, i, '\"'))
			malloc_word(str, &i, &split_string[words_count++], '\"');
		if (str[i] != ' ' && str[i])
			split_string[words_count++] = (char *)malloc(sizeof(char) *
					(not_qs_char_count(str, &i) + 1));
		if (str[i])
			i++;
	}
	return (split_string);
}

int		count_words(char *str, int i, int count)
{
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes_check(str, i, '\''))
		{
			i++;
			char_count(str, &i, '\'');
			count++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '\"' && closed_quotes_check(str, i, '\"'))
		{
			i++;
			char_count(str, &i, '\"');
			count++;
			if (str[i] == '\"')
				i++;
		}
		if (str[i] != ' ' && str[i])
		{
			not_qs_char_count(str, &i);
			count++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

void	*split_string_malloc(char **split_string, char *str)
{
	split_string = (char **)malloc(sizeof(char *) *
								   (count_words(str, 0, 0) + 1));
	if (!split_string)
		return (NULL);
	return (split_words_malloc(split_string, str));
}


char	**split_line(char *str)
{
	char	**split_string;
	int		i;
	int 	words_count;

	split_string = NULL;
	split_string = split_string_malloc(split_string, str);
	words_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && closed_quotes_check(str, i, '\''))
			copy_word(str, &i, &split_string[words_count++], '\'');
		if (str[i] == '\"' && closed_quotes_check(str, i, '\"'))
			copy_word(str, &i, &split_string[words_count++], '\"');
		if (str[i] != ' ' && str[i])
			copy_space_word(str, &i, &split_string[words_count++]);
		if (str[i])
			i++;
	}
	split_string[words_count] = NULL;
	return (split_string);
}
int	main(void)
{
	char 	*str;
	char	**tmp;
	int i;

	//str = ft_strdup("\"foo | bar\" | pwd one |ls two three \'four five |"
	//		"\"hello world\" \'okay | \' not okay");
	str = ft_strdup(" \'hello world | \'fo ba\' \"|\" yes\' now ");
	tmp = split_line(str);
	i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	printf("%s\n", tmp[i]);
	return (0);
}