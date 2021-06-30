#include "../libft/libft.h"
#include <stdio.h>

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
		{
			k = i;
			i++;
			while (str[i] != '\"' && str[i])
				i++;
			if (str[i] != '\"')
				i = k;
		}
		if (str[i] == '\'')
		{
			k = i;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] != '\'')
				i = k;
		}
		if (str[i] == '|')
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

static void	*cmd_line_malloc(char **str_arr, char *str)
{
	int	cl_count;
	int	i;
	int k;
	int	chr_count;

	cl_count = 0;
	chr_count = 0;
	k = 0;
	i = 0;
	while (str[i] != '|')
	{
		if (str[i] == '\"')
		{
			k = i;
			i++;
			while (str[i] != '\"' && str[i])
				i++;
			if (str[i] != '\"')
				i = k;
		}
		if (str[i] == '\'')
		{
			k = i;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] != '\'')
				i = k;
		}
		i++;
	}
	return (str_arr);
}

void	*cmd_lines_malloc(char **str_arr, char *str)
{
	int	count;

	count = command_line_count(str);
	str_arr = (char **)malloc(sizeof(char *) * (count + 2));
	if (!str_arr)
		return (NULL);
	return (cmd_line_malloc(str_arr, str));
}

char	**split_cmds(char *str)
{
	char	**str_arr;
	int		str_i;
	int		chr_i;
	int		i;

	str_arr = NULL;
	str_arr = cmd_lines_malloc(str_arr, str);
	str_i = 0;
	i = 0;
	while (str[i])
	{
		chr_i = 0;
		while (str[i])
		{
			if (str[i] == '|')
				break ;
			str_arr[str_i][chr_i++] = str[i++];
		}
		str_arr[str_i++][chr_i] = '\0';
		if (str[i])
			i++;
	}
	str_arr[str_i] = NULL;
	return (str_arr);
}

int	main(void)
{
	char *str;
	char	**tmp;
	int count;
	int i;
	int k;
	int z;
	int lines_count;
	int start;

	str = ft_strdup("\"foo | bar\" |pwd one|ls two three \'four five\' |"
			"\"hello ' world\" \'okay | \' not okay");
	/*count = command_line_count(str);
	printf("count = %d\n", count);
	tmp = split_cmds(str);
	i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	printf("%s\n", tmp[i]);*/
	z = 0;
	lines_count = 0;
	while (str[z])
	{
		i = z;
		start = i;
		printf("start from %c | ", str[z]);
		while (str[i] != '|' && str[i])
		{
			if (str[i] == '\"')
			{
				k = i;
				i++;
				while (str[i] != '\"' && str[i])
					i++;
				if (str[i] != '\"')
					i = k;
			}
			if (str[i] == '\'')
			{
				k = i;
				i++;
				while (str[i] != '\'' && str[i])
					i++;
				if (str[i] != '\'')
					i = k;
			}
			i++;
		}
		lines_count++;
		printf("line number %d have %d sym\n", lines_count, i - start);
		z = i;
		if (str[z])
			z++;
	}
	return (0);
}