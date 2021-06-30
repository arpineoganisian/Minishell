#include "../libft/libft.h"
#include <stdio.h>

void quotes_handle(char *str, int *i, char c)
{
	int	k;

	k = *i;
	(*i)++;
	while (str[*i] != c && str[*i])
		(*i)++;
	if (str[*i] != c)
		*i = k;
}

int command_line_count(char *str)
{
	int	i;
	int k;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quotes_handle(str, &i, '\"');
		if (str[i] == '\'')
			quotes_handle(str, &i, '\'');
		if (str[i] == '|')
			count++;
		if (str[i])
			i++;
	}
	return (count + 1);
}

void	line_char_count(char *str, int *i)
{
	int tmp_i;

	while (str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\"')
		{
			tmp_i = *i;
			(*i)++;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
			if (str[*i] != '\"')
				*i = tmp_i;
		}
		if (str[*i] == '\'')
		{
			tmp_i = *i;
			(*i)++;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
			if (str[*i] != '\'')
				*i = tmp_i;
		}
		(*i)++;
	}
}

void	*cmd_line_malloc(char **str_arr, char *str)
{
	int	cl_count;
	int	i;
	int	start;

	cl_count = 0;
	i = 0;
	while (str[i])
	{
		start = i;
		line_char_count(str, &i);
		str_arr[cl_count] = (char *) malloc(sizeof(char) * (i - start + 1));
		cl_count++;
		if (str[i])
			i++;
	}
	return (str_arr);
}

void	*cmd_lines_malloc(char **str_arr, char *str)
{
	int	count;

	count = command_line_count(str);
	str_arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str_arr)
		return (NULL);
	return (cmd_line_malloc(str_arr, str));
}

char	**split_cmds(char *str)
{
	char	**str_arr;
	int		cl_count;
	int		i;
	int 	cmd_chr;
	int		start;

	str_arr = NULL;
	str_arr = cmd_lines_malloc(str_arr, str);
	cl_count = 0;
	i = 0;
	while (str[i])
	{
		start = i;
		line_char_count(str, &i);
		cmd_chr = 0;
		while (start <= i - 1)
			str_arr[cl_count][cmd_chr++] = str[start++];
		str_arr[cl_count][cmd_chr] = '\0';
		cl_count++;
		if (str[i])
			i++;
	}
	str_arr[cl_count] = NULL;
	return (str_arr);
}

int	main(void)
{
	char *str;
	char	**tmp;
	int i;

	str = ft_strdup("\"foo | bar\" |pwd one|ls two three \'four five\' |"
			"\"hello ' world\" \'okay | \' not okay");
	tmp = split_cmds(str);
	i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	printf("%s\n", tmp[i]);
	return (0);
}