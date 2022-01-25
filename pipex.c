/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/25 21:03:58 by rschleic         ###   ########.fr       */
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

void	exec(char *cmd, char **envp)
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
		i++;
	}
	
}
int main (int argc, char **argv, char **envp)
//envp exists by default, just declare so it's there
{
	int	in;
	int	out;
	
	if (argc != 5)
		exec_failed("ERROR: incorrect parameter number");
	
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		exec_failed("ERROR: inputfile failure");
	out = open(argv[4], O_RDWR | O_CREAT , 0644);
	//0644 to be able to open what was just created
	if (out == -1)
	{
		close(in);
		exec_failed("ERROR: outputfile failure");
	}
	
	int fildes[2];
	//the two files needed to use pipe
	
	if (pipe(fildes) == -1)
	//here the pipe with its two ffiles gets created
		exec_failed("ERROR: unsuccessful creation of pipe");
	
	// pid_t	pid = fork();
	// if (pid == -1)
	// 	exec_failed("ERROR: unsuccessful fork execution");
	// if (pid == 0) {
		
	// 	dup2(in, STDIN_FILENO);
	// 	dup2(fildes[1], STDOUT_FILENO);
		exec(argv[2], envp);
		//redirecting correctly!
		//child execve whileloop
// 	}
// 	else {
// 		dup2(fildes[0], STDIN_FILENO);
// 		dup2(out, STDOUT_FILENO);
// 		//redirecting correctly!
// 		//parent execve whileloop
// 	}
	
// 	char **args = ft_split(argv[2], ' '); // split the command
// 	dup2(in, STDIN_FILENO);
// 	dup2(out, STDOUT_FILENO);
// 	execve("/bin/cat", args, envp); //read from 0 -> write to 1
	
}

/*	open filedescriptors for in and out
	split the command string
	redirect stdin and stdout execve
	execve takes the command path, the command, and envp =?
*/
