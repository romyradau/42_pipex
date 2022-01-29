/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/29 22:01:27 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirecting_child(int in, int *fd, char *cmd, char **envp)
{
	close(out);
	//offene fds amchend ie liste ewig lang
	//bei pipes mussen alle zeiger auf files zerstort werden
	dup2(in, STDIN_FILENO);
	close(in);
	//sobald man eine verbindung nicht mehr braucht kann man die loschen
	//aufs infile kann man jetzt über 4 und 0 zugreifen
	close(fd[READ_END]);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	cmd_exec(cmd, envp);
}

void	redirecting_parent(int out, int *fd, char *cmd, char **envp)
//ier ist wieder ales unberúrt
{
	close(in);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	//kann man kaputt machen weil die verbindung uber die null steht.
	close(fd[READ_END]);
	dup2(out, STDOUT_FILENO);
	//wo des erste hinzeigt, zeigt dann auch das zweite hin
	close(out);
	cmd_exec(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		in;
	int		out;
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
		//must be different for bonus
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		exec_failed("ERROR: open infile failure");
	out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		close(in);
		//explain
		exec_failed("ERROR: open outfile failed");
	}
	if (pipe(fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	pid = fork();
	if (pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (pid == 0)
		redirecting_child(in, fd, argv[2], envp);
	child_status();
	redirecting_parent(out, fd, argv[3], envp);
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
	
/*
	instead of else for the parent
	we can just waitpid(pid, NULL, 0);
	...
*/
	/*
		envp exists by default, just declare so it's there
		They will be readable by all the user groups
		but writable by the user only.
		These permissions are set automatically when the file is created.
		| here means bitwise "or", so that both macros will be found there
		0644 to be able to open what was just created
	*/
