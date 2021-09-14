#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

size_t	str_size(char **str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char *new;
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(str);
	if (!len)
		return (NULL);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	error_out(const int i, const char *str)
{
	write(ERR, "pipex:", 7);
	(i == 2) && write(ERR, " can't create struct", 21);
	(i == 3) && write(ERR, " fatal", 7);
	if (i == 4)
		perror(str);
	(i == 5) && write(ERR, str, ft_strlen(str));
	if (i == 6) 
	{
		write(ERR, str, ft_strlen(str));
		write(ERR, ": command not found", 20);
	}
	write(ERR, "\n", 1);
	return (-1);
}
