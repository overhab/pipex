#include "pipex.h"

int	free_str(char **str, size_t size)
{
	size_t i;

	i = 0;
	if (!str)
		return 0;
	while (i < size)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}

void	clean_struct(t_pipex *pipex)
{
	free_str(pipex->cmd_1, pipex->size_1);
	free_str(pipex->cmd_2, pipex->size_2);
	free(pipex);
}

static int	init_struct(t_pipex **pp, char **env, char **av)
{
	t_pipex *pipex;

	pipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (0);
	pipex->env = env;
	pipex->filein = av[1];
	pipex->fileout = av[4];
	pipex->cmd_1 = ft_split(av[2], ' ');
	pipex->size_1 = count_words(av[2]);
	pipex->cmd_2 = ft_split(av[3], ' ');
	pipex->size_2 = count_words(av[3]);
	pipex->error = 0;
	*pp = pipex;
	return (1);
}

void	free_and_close(t_pipex *pipex)
{
	if (pipex->path_1)
		free(pipex->path_1);
	if (pipex->path_2)
		free(pipex->path_2);
	close(pipex->ffd[IN]);
	close(pipex->ffd[OUT]);
}

int		main(int ac, char **av, char **env)
{
	t_pipex		*pipex;

	pipex = NULL;
	if (ac != 5)
	{
		write(ERR, "Error: wrong arguments\n", 24);
		return (0);
	}
	else
	{
		if (!init_struct(&pipex, env, av))
			return (error_out(1, NULL));
		start_process(pipex);
		clean_struct(pipex);
	}
	return (0);
}
