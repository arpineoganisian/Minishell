/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjonell <thjonell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:44:13 by thjonell          #+#    #+#             */
/*   Updated: 2021/05/29 16:39:31 by thjonell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

static void	**ft_free(char **strs, int i)
{
	while (i >= 0)
		free(strs[i--]);
	free(strs);
	return (NULL);
}

static void	*ft_strmalloc(char **strs, char const *s, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
		{
			j = 0;
			while (s[k] != c && s[k] != '\0')
			{
				k++;
				j++;
			}
			strs[i] = (char *)malloc(sizeof(char) * (j + 1));
			if (!strs[i])
				return (ft_free(strs, i));
			i++;
		}
		if (s[k] != '\0')
			k++;
	}
	return (strs);
}

static void	*ft_strsmalloc(char **strs, char const *s, char c)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
			i++;
		while (s[k] != c && s[k])
			k++;
		if (s[k])
			k++;
	}
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	return (ft_strmalloc(strs, s, c));
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		k;

	strs = NULL;
	strs = ft_strsmalloc(strs, s, c);
	if (!s || !strs)
		return (NULL);
	i = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
		{
			j = 0;
			while (s[k] != c && s[k] != '\0')
				strs[i][j++] = s[k++];
			strs[i++][j] = '\0';
		}
		if (s[k])
			k++;
	}
	strs[i] = NULL;
	return (strs);
}

int	main(void)
{
	char *str = "hello world ; 21 school";
	char ***array;
	char **tmp;
	int	i;
	int k;
	int count;

	/*
	 * 	tmp = {"hello world ", " 21 school"};
	 * 	tmp2 = ft_split(tmp[0], ' ');
	 * 	tmp2 = {"hello", "world"};
	 * 	tmp3 = ft_split(tmp[1], ' ');
	 * 	tmp3 = {"21", "school"};
	 * array = {{"hello", "world"}, {"21", "school"}};
	 * array[0] = {"hello", "world"};
	 * array[0][0] = "hello";
	 */
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ';')
			count++;
		i++;
	}
	array = malloc(sizeof(char **) * (count + 2));
	tmp = ft_split(str, ';');
	i = 0;
	while (tmp[i])
	{
		array[i] = ft_split(tmp[i], ' ');
		i++;
	}
	array[i] = NULL;
	i = 0;
	while (array[i])
	{
		k = 0;
		printf("%d cmd = %s\n", i + 1, array[i][k]);
		k++;
		while (array[i][k])
		{
			printf("%d arg = %s\n", k, array[i][k]);
			k++;
		}
		i++;
	}
	return (0);
}