#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define IN 0
# define OUT 1
# define ERR 2

# define RED 	 "\033[1;31m"
# define GREEN   "\033[0;32m"
# define YELLOW	 "\033[1;33m"
# define BLUE	 "\033[1;34m"
# define PURPLE  "\033[1;35m"
# define CYAN    "\033[1;36m"
# define RESET   "\033[0;0m"
# define BOLD    "\033[;1m"
# define REVERSE "\033[;7m"

typedef struct s_pipex
{
	char		**env;
	char		**cmd_1;
	size_t		size_1;
	char		**cmd_2;
	size_t		size_2;
	char		*filein;
	char		*fileout;
	char		*path_1;
	char		*path_2;
	int			fd[2];
	int			ffd[2];
	int			error;
	int			status;
}	t_pipex;

/* 
** MAIN 
*/
void	clean_struct(t_pipex *pipex);
char	*find_path(t_pipex *pipex, char *name);
int		check_path(t_pipex *pipex, char *name, char **path);
void	exec_cmd(t_pipex *pipex);
void	free_and_close(t_pipex *pipex);

/* 
**EXECUTE
*/
int		start_process(t_pipex *pipex);


/* 
** UTILS 
*/
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *str, int character, size_t n);
size_t	ft_strlen(const char *str);
size_t	count_words(char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		space_skip(const char *nptr, int index);
int		free_str(char **str, size_t size);
size_t	str_size(char **str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *str);

/* 
** ERRORS 
*/

int		error_out(const int i, const char *str);

#endif
