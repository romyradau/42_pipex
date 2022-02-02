/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/02 22:23:50 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	redirecting_child(t_file *file, char *cmd, char **envp)
{
	close(file->out);
	//offene fds amchend ie liste ewig lang
	//bei pipes mussen alle zeiger auf files zerstort werden
	dup2(file->in, STDIN_FILENO);
	close(file->in);
	//sobald man eine verbindung nicht mehr braucht kann man die loschen
	//aufs infile kann man jetzt über 4 und 0 zugreifen
	close(file->fd[READ_END]);
	dup2(file->fd[WRITE_END], STDOUT_FILENO);
	close(file->fd[WRITE_END]);
	cmd_exec(cmd, envp);
}

//close and dup2 error check


void	redirecting_parent(t_file *file, char *cmd, char **envp)
//ier ist wieder ales unberúrt
{
	close(file->in);
	close(file->fd[WRITE_END]);
	dup2(file->fd[READ_END], STDIN_FILENO);
	//kann man kaputt machen weil die verbindung uber die null steht.
	close(file->fd[READ_END]);
	dup2(file->out, STDOUT_FILENO);
	//wo des erste hinzeigt, zeigt dann auch das zweite hin
	close(file->out);
	cmd_exec(cmd, envp);
}

//close and dup2 error check


int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	pid_t	pid;

	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
		//must be different for bonus
	file.in = open(argv[1], O_RDONLY);
	if (file.in == -1)
		exec_failed("ERROR: open infile failure");
	file.out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file.out == -1)
	{
		close(file.in);
		//explain
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

if (pipe(fd) == -1)
	exec_failed("ERROR: unsuccessful creation of pipe");
pid = fork();
if (pid == -1)
	exec_failed("ERROR: unsuccessful fork execution");
if (pid == 0)
	redirecting_child(in, fd, argv[2], envp);
child_status();

this needs to be replaced by a while loop
	

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
