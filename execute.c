#include "pipex.h"

int		openfiles(t_pipex *pipex)
{
	int		flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->ffd[IN] = open(pipex->filein, O_RDONLY);
	if (pipex->ffd[0] == -1)
		return (error_out(4, pipex->filein));
	pipex->ffd[OUT] = open(pipex->fileout, flags, 0644);
	if (pipex->ffd[1] == -1)
		return (error_out(5, "output file\n"));
	return (0);
}

int		start_process(t_pipex *pipex)
{
	if (openfiles(pipex) == -1)
		return (-1);
	if (pipe(pipex->fd) < 0)
		return (error_out(3, NULL));	
	check_path(pipex, pipex->cmd_1[0], &pipex->path_1);
	check_path(pipex, pipex->cmd_2[0], &pipex->path_2);
	if (!pipex->error)
		exec_cmd(pipex);
	free_and_close(pipex);
	return (0);
}

void	exit_error(int type, char *str, t_pipex *pipex)
{
	write(ERR, "pipex:", 7);
	(type == 1) && write(ERR, " fatal\n", 8);
	if (type == 2)
	{
		if (errno == EISDIR)
			perror(strerror(EISDIR));
		else
			perror(str);
	}
	free_and_close(pipex);
	clean_struct(pipex);
	exit(EXIT_FAILURE);
}

void	process_dup2(t_pipex *pipex, int type)
{
	(type == 1) && close(pipex->fd[IN]);
	(type == 2) && close(pipex->fd[OUT]);
	if (type == 1 && dup2(pipex->fd[OUT], OUT) < 0)
		exit_error(1, NULL, pipex);
	if (type == 2 && dup2(pipex->fd[IN], IN) < 0)
		exit_error(1, NULL, pipex);
	if (type == 1 && dup2(pipex->ffd[IN], IN) < 0)
		exit_error(1, NULL, pipex);
	if (type == 2 && dup2(pipex->ffd[OUT], OUT) < 0)
		exit_error(1, NULL, pipex);
	(type == 2) && close(pipex->fd[IN]);
	(type == 1) && close(pipex->fd[OUT]);
}

void	exec_cmd(t_pipex *pipex)
{
	pid_t	pid;
	int 	status;

	pid = fork();
	if (pid < 0)
		exit_error(1, NULL, pipex);
	else if (pid == 0)
	{
		process_dup2(pipex, 1);
		if (execve(pipex->path_1, pipex->cmd_1, pipex->env) < 0)
			exit_error(2, pipex->cmd_1[0], pipex);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		process_dup2(pipex, 2);
		if (execve(pipex->path_2, pipex->cmd_2, pipex->env) < 0)
			exit_error(2, pipex->cmd_2[0], pipex);
	}
}
