/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/04 00:27:33 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	redirecting_child(t_file *file, char *cmd, char **envp)
{
	int	error;
	
	error = (
	close(file->out)
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

	/*
	if -1 success it will be 1
	offene fds machen die liste ewig lang
	bei pipes mussen alle zeiger auf files zerstort werden
	sobald man eine verbindung nicht mehr braucht kann man die loschen
	sobald man in einen anderen prozess geht ist wieder alle fds etc unberührt
	*/

int	redirecting_parent(t_file *file, char *cmd, char **envp)
{
	int	error;
	
	error = (
	close(file->in)
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

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	pid_t	pid;

	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
	file.in = open(argv[1], O_RDONLY);
	if (file.in == -1)
		exec_failed("ERROR: open infile failure");
	file.out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file.out == -1)
	{
		close(file.in);
		exec_failed("ERROR: open outfile failed");
	}
	if (pipe(file.fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	pid = fork();
	if (pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (pid == 0)
		redirecting_child(&file, argv[2], envp);
	child_status();
	redirecting_parent(&file, argv[3], envp);
}
/*
	instead of else for the parent
	we can just waitpid(pid, NULL, 0);
	...
	

		envp exists by default, just declare so it's there
		They will be readable by all the user groups
		but writable by the user only.
		These permissions are set automatically when the file is created.
		| here means bitwise "or", so that both macros will be found there
		0644 to be able to open what was just created
*/
