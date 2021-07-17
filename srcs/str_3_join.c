#include "minishell.h"

char	*str_3_join(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	int		i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		*(str + i++) = *s1++;
	while (*s2)
		*(str + i++) = *s2++;
	while (*s3)
		*(str + i++) = *s3++;
	*(str + i) = '\0';
	return (str);
}