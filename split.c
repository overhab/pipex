#include "pipex.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	indx;
	size_t	wordcount;

	indx = 0;
	wordcount = 0;
	while (s[indx])
	{
		while (s[indx] == c)
			indx++;
		wordcount++;
		while (s[indx] && s[indx] != c)
			indx++;
	}
	return (wordcount);
}

static void		ft_free(char **splt, size_t wordcount)
{
	size_t i;

	i = 0;
	while (wordcount)
	{
		free(splt[i++]);
		wordcount--;
	}
	free(splt);
}

static char		**ft_strings(const char *s, char c, char **splt)
{
	size_t nextword;
	size_t indx;
	size_t tab;

	indx = 0;
	tab = 0;
	while (s[indx])
	{
		while (s[indx] == c)
			indx++;
		nextword = indx;
		while (s[indx] && s[indx] != c)
			indx++;
		if (indx > nextword)
		{
			if (!(splt[tab] = ft_substr(s + nextword, 0,  indx - nextword)))
			{
				ft_free(splt, ft_count(s, c));
				return (0);
			}
			tab++;
		}
	}
	splt[tab] = 0;
	return (splt);
}

char			**ft_split(char const *s, char c)
{
	char		**splt;

	if (!s || !(splt = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1))))
		return (0);
	splt = ft_strings(s, c, splt);
	return (splt);
}
