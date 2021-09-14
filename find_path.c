#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char *rmd, char *buffer)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	indx;

	len1 = ft_strlen(rmd);
	len2 = ft_strlen(buffer);
	indx = 0;
	str = (char *)malloc((len1 + len2 + 1) * sizeof(*str));
	if (str == NULL)
	{
		if (rmd)
			free(rmd);
		return (0);
	}
	while (len1--)
	{
		str[indx] = rmd[indx];
		indx++;
	}
	while (len2--)
		str[indx++] = *buffer++;
	str[indx] = '\0';
	return (str);
}

char	*my_getenv(t_pipex *pipex, char *key)
{		
	char		*value;
	size_t		i;

	i = 0;
	if (!key)
		return (NULL);
	while (pipex->env[i])
	{
		if (!ft_strncmp(pipex->env[i], key, ft_strlen(key)))
		{
			value = pipex->env[i] + ft_strlen(key);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(t_pipex *pipex, char *name)
{
	char	**env_paths;
	char	**mem;
	char	*path;
	char	*mid;

	path = 0;
	env_paths = ft_split(my_getenv(pipex, "PATH="), ':');
	if (env_paths == NULL)
		return (NULL);
	mem = env_paths;
	mid = ft_strjoin("/", name);
	while (*env_paths && *name != '\0')
	{
		path = ft_strjoin(*env_paths, mid);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		env_paths++;
	}
	free(mid);
	free_str(mem, str_size(mem));
	return (path);
}

int	check_path(t_pipex *pipex, char *name, char **path)
{
	if (!ft_strchr(name, '/'))
	{
		*path = find_path(pipex, name);
		if (*path == NULL)
			pipex->error = error_out(6, name);
		return (0);
	}
	else
	{
		*path = ft_strdup(name);
		if (access(*path, F_OK) != 0)
		{
			pipex->error = -1;
			perror(*path);
		}
		return (0);
	}
}
