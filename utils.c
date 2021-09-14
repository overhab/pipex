#include "pipex.h"

void	*ft_memset(void *str, int character, size_t n)
{
	while (n--)
		((unsigned char *)str)[n] = (unsigned char)character;
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(size * count);
	if (p)
		ft_memset(p, 0, (size * count));
	return (p);
}

size_t	count_words(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 1;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		i++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	d;

	i = 0;
	d = 0;
	if (!s)
		return (0);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (0);
	while (s[d])
	{
		if (d == start && i < len)
		{
			sub[i] = s[d];
			i++;
			start++;
		}
		d++;
	}
	sub[i] = 0;
	return (sub);
}

int	space_skip(const char *nptr, int index)
{
	while ((nptr[index] == ' ') || (nptr[index] == '\n')
		|| (nptr[index] == '\f') || (nptr[index] == '\v')
		|| (nptr[index] == '\r') || (nptr[index] == '\t'))
		index++;
	return (index);
}
