/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/07 19:59:07 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	redirecting_child(t_file *file, char *cmd, char **envp)
{
	int	error;

	error = (
			close(file->out) == -1
			|| dup2(file->in, STDIN_FILENO) == -1
			|| close(file->in) == -1
			|| close(file->fd[READ_END]) == -1
			|| dup2(file->fd[WRITE_END], STDOUT_FILENO) == -1
			|| close(file->fd[WRITE_END]) == -1
			);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

int	redirecting_parent(t_file *file, char *cmd, char **envp)
{
	int	error;

	error = (
			close(file->in) == -1
			|| close(file->fd[WRITE_END]) == -1
			|| dup2(file->fd[READ_END], STDIN_FILENO) == -1
			|| close(file->fd[READ_END]) == -1
			|| dup2(file->out, STDOUT_FILENO) == -1
			|| close(file->out) == -1
			);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

	/*
	if -1 success it will be 1
	*/

void	open_files(char **argv, t_file *file)
{
	file->in = open(argv[1], O_RDONLY);
	if (file->in == -1)
		exec_failed("ERROR: open infile failure");
	file->out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file->out == -1)
	{
		close(file->in);
		exec_failed("ERROR: open outfile failed");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	pid_t	pid;

	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
	open_files(argv, &file);
	if (pipe(file.fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	pid = fork();
	if (pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (pid == 0)
	{
		if (redirecting_child(&file, argv[2], envp))
			exec_failed("ERROR: open/close failure in childprocess");
	}
	waitpid(pid, NULL, 0);
	if (redirecting_parent(&file, argv[3], envp))
		exec_failed("ERROR: open/close failure in parentprocess");
}
