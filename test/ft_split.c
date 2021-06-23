#include "../libft/libft.h"
#include <stdio.h>

static void	**ft_free(char **str_arr, int i)
{
	while (i >= 0)
		free(str_arr[i--]);
	free(str_arr);
	return (NULL);
}

static void	*ft_strmalloc(char **str_arr, char const *str, char c)
{
	int	str_i;
	int	i;
	int	chr_i;

	str_i = 0;
	i = 0;
	while (str[i])
	{
		chr_i = 0;
		while (str[i])
		{
			if (str[i] == c && str[i - 1] != '\'' && str[i - 1] != '\"'
				&& str[i - 1] != '\\')
				break ;
			chr_i++;
			i++;
		}
		str_arr[str_i] = (char *)malloc(sizeof(char) * (chr_i + 1));
		if (!str_arr[str_i])
			return (ft_free(str_arr, str_i));
		if (str[i])
			i++;
		str_i++;
	}
	return (str_arr);
}

static void	*ft_strsmalloc(char **str_arr, char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		while (str[i])
		{
			if (str[i] == c && str[i - 1] != '\'' && str[i - 1] != '\"'
				&& str[i - 1] != '\\')
				break ;
			i++;
		}
		if (str[i])
			i++;
	}
	str_arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str_arr)
		return (NULL);
	return (ft_strmalloc(str_arr, str, c));
}

char	**smart_split(char const *str, char c)
{
	char	**str_arr;
	int		str_i;
	int		chr_i;
	int		i;

	str_arr = NULL;
	str_arr = ft_strsmalloc(str_arr, str, c);
	str_i = 0;
	i = 0;
	while (str[i])
	{
		chr_i = 0;
		while (str[i])
		{
			if (str[i] == c && str[i - 1] != '\'' && str[i - 1] != '\"'
				&& str[i - 1] != '\\')
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
	char *str = "echo";
	char **array_str;
	int i;

	array_str = smart_split(str, ';');
	i = 0;
	while (array_str[i])
	{
		printf("%s\n", array_str[i]);
		i++;
	}
	printf("%s\n", array_str[i]);
	return (0);
}