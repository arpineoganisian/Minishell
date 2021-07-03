#include "minishell.h"

char	*make_filename(char *str, int i, t_data *data)
{
	int		tmp;
	char	*tmp_str;

	if (str[i] == '\"' && closed_quotes(str, i, '\"'))
	{
		tmp = i;
		while (str[++i] != '\"')
			;
	}
	else if (str[i] == '\'' && closed_quotes(str, i, '\''))
	{
		tmp = i;
		while (str[++i] != '\'')
			;
	}
	else
	{
		tmp = i;
		while (str[++i] != ' ' && str[i])
			;
	}
	tmp_str = ft_substr(str, tmp, i - tmp + 1);
	spec_sym_handler(&tmp_str, data);
	return (tmp_str);
}

void	skip_other(char *str, int *i)
{
	while (str[*i] != '>' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
		{
			(*i)++;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
		}
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
		{
			(*i)++;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
		}
		if (str[*i])
			(*i)++;
	}
}