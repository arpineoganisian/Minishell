#include "minishell.h"

char	*slash_handler(char *str, int *i)
{
	char	*tmp;
	char	*t_tmp;

	tmp = ft_substr(str, 0, *i);
	t_tmp = ft_strjoin(tmp, str + *i + 1);
	free(tmp);
	return (t_tmp);
}

char	*quotes_handler(char *str, int *i)
{
	char	*tmp;
	char	*s_tmp;
	char	*t_tmp;
	int		j;

	j = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	tmp = ft_substr(str, 0, j);
	s_tmp = ft_substr(str, j + 1, *i - j - 1);
	t_tmp = ft_strjoin(tmp, s_tmp);
	free(s_tmp);
	free(tmp);
	tmp = ft_strjoin(t_tmp, str + *i + 1);
	free(t_tmp);
	return (tmp);
}

char	*dquotes_handler(char *str, int *i)
{
	char	*tmp;
	char	*s_tmp;
	char	*t_tmp;
	int		j;

	j = *i;
	(*i)++;
	while (str[*i] != '\"')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '\\' ||
		str[*i + 1] == '$'))
			str = slash_handler(str, i);
		if (str[*i] && str[*i] != '\n')
			(*i)++;
	}
	tmp = ft_substr(str, 0, j);
	s_tmp = ft_substr(str, j + 1, *i - j - 1);
	t_tmp = ft_strjoin(tmp, s_tmp);
	free(s_tmp);
	free(tmp);
	tmp = ft_strjoin(t_tmp, str + *i + 1);
	free(t_tmp);
	return (tmp);
}

char	*spec_sym_handler(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] == '\'')
			str = quotes_handler(str, &i);
		if (str[i] == '\"')
			str = dquotes_handler(str, &i);
		if (str[i] == '\\')
			str = slash_handler(str, &i);
		if (str[i] != '\n' && str[i] != '\0')
			i++;
	}
	return (str);
}