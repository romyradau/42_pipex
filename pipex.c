/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/26 17:33:35 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void	cp_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_args;
	char	*match;
	//free strjoin
	paths = ft_split(envp[29] + 6, ':');
	//find the right envpath
	int i = 0;
	while (paths[i])
	{
		match = ft_strjoin(paths[i], '/');
		match = ft_strjoin(match, cmd);
		if (access(match, F_OK) == 0)
		{
			cmd_args = ft_split(cmd, ' ');
			execve(match, cmd_args, envp);
			//execve magic, executes the cmd plus its arguments
		}
		else
			exec_failed("no matching path found\n");
		i++;
	}
	
}

int main (int argc, char **argv, char **envp)
//envp exists by default, just declare so it's there
{
	int		in;
	int		out;
	int		pfd[2];
	pid_t	cpid;
	int		wait_status;
	int		status_code;
	pid_t	pid;
	
	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		exec_failed("ERROR: inputfile failure");
	out = open(argv[4], O_RDWR | O_CREAT , 0644);
	/*They will be readable by all the user groups
		but writable by the user only. These permissions are set automatically when the file is created.
	| here means bitwise "or" them, so that both macros will be found there??
	0644 to be able to open what was just created */
	if (out == -1)
	{
		close(in);
		exec_failed("ERROR: outputfile failure");
	}
	if (pipe(pfd) == -1)
	//here the pipe with its two files gets created
		exec_failed("ERROR: unsuccessful creation of pipe");
	pid = fork();
	if (pid == -1)
	exec_failed("ERROR: unsuccessful fork execution");
	if (pid == 0) {
	// 	dup2(in, STDIN_FILENO);
		close(pfd[0]);
		close(pfd[1]);
	// 	dup2(pfd[1], STDOUT_FILENO);
		cp_exec(argv[2], envp);
		//redirecting correctly!
		//child execve whileloop
// 	}
//need to also close mains fd's
	close(pfd[0]);
	close(pfd[1]);
/* instead of else for the parent
	we can just waitpid(pid, NULL, 0); 
	...
*/
// 	else {
		wait(&wait_status);
		//but whats wait_status, you didn't declare it yet
		if (WIFEXITED(wait_status))
		//WIFEXITED checks that it exits
		{
			status_code = WEXITSTATUS(wait_status);
			//if (WEXITSTATUS(wait_status) == 0)
				//what then?? (success)
			//WEXITSTATUS checks with what it exited
		}
		//to check if wait was successful
// 		dup2(pfd[0], STDIN_FILENO);
// 		dup2(out, STDOUT_FILENO);
// 		//redirecting correctly!
// 		//parent execve whileloop
// 	}
}

/*	open filedescriptors for in and out
	split the command string
	redirect stdin and stdout execve
	execve takes the command path, the command, and envp
*/
