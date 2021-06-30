#include "minishell.h"

int 	in_quotes(char *str, int i)
{
	int	k;

	while (i >= 0)
	{
		if (str[i] == '\'')
		{
			k = i;
			while (str[++k])
			{
				if (str[k] == '\'')
					return (1);
			}
		}
		if (str[i] == '\"')
		{
			k = i;
			while (str[++k])
			{
				if (str[k] == '\"')
					return (1);
			}
		}
		i--;
	}
	return (0);
}

static void	*ft_strmalloc(char **str_arr, char *str, char c)
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
			if (str[i] == c && !in_quotes(str, i))
				break ;
			chr_i++;
			i++;
		}
		str_arr[str_i] = (char *)malloc(sizeof(char) * (chr_i + 1));
		if (!str_arr[str_i])
			return (NULL);
		if (str[i])
			i++;
		str_i++;
	}
	return (str_arr);
}

static void	*ft_strsmalloc(char **str_arr, char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && !in_quotes(str, i))
			count++;
		i++;
	}
	str_arr = (char **)malloc(sizeof(char *) * (count + 2));
	if (!str_arr)
		return (NULL);
	return (ft_strmalloc(str_arr, str, c));
}

char	**smart_split(char *str, char c)
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
			if (str[i] == c && !in_quotes(str, i))
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

void	split_cmd(t_data *data)
{
	char	**tmp;
	int	i;
	int k;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '|' && !in_quotes(data->str, i))
			data->cmd_count++;
		i++;
	}
	data->cmd_lines = (char ***)malloc(sizeof(char **) * (data->cmd_count + 2));
	tmp = smart_split(data->str, '|');
	i = 0;
	while (tmp[i])
	{
//		if (spec_sym_handler(&tmp[i], data))
//			return ;
		data->cmd_lines[i] = split_line(tmp[i]);
		ft_putstr_fd("cmd line number ", 1);
		ft_putnbr_fd(i + 1, 1);
		ft_putstr_fd(":\n", 1);
		k = 0;
		while (data->cmd_lines[i][k])
		{
			ft_putnbr_fd(k + 1, 1);
			ft_putstr_fd(" elem = ", 1);
			ft_putstr_fd(data->cmd_lines[i][k], 1);
			ft_putstr_fd(" ", 1);
			k++;
		}
		ft_putstr_fd("\n", 1);
		//execute_cmd(data->cmd_lines[i], data);
		i++;
		//free tmp
	}
	data->cmd_lines[i] = NULL;
}
