/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/27 19:31:32 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int	child_status(void);

void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}


void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	cp_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_args;
	char	*match;
	char	*tmp_match;
	int		i;
	i = 0;
	while(ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 6, ':');
	cmd_args = ft_split(cmd, ' ');
	i = 0;
	while (paths[i])
	{
		tmp_match = ft_strjoin(paths[i], "/");
		match = ft_strjoin(tmp_match, cmd_args[0]);
		free(tmp_match);

		if (access(match, F_OK) == 0)
		{
			execve(match, cmd_args, envp);
			//execve magic, executes the cmd plus its arguments
		}
		free(match);
		i++;
	}
	exec_failed("no matching path found\n");
	free_split(paths);
	free_split(cmd_args);
}

int main (int argc, char **argv, char **envp)
//envp exists by default, just declare so it's there
{
	int		in;
	int		out;
	int		fd[2];
	pid_t	pid;
	
	// if (argc != 5)
	// 	exec_failed("ERROR: incorrect parameter number");
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		exec_failed("ERROR: inputfile failure");
	// out = open(argv[4], O_RDWR | O_CREAT , 0644);
	out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	/*They will be readable by all the user groups
		but writable by the user only. These permissions are set automatically when the file is created.
		| here means bitwise "or" them, so that both macros will be found there??
	0644 to be able to open what was just created */
	if (out == -1)
	{
		close(in);
		exec_failed("ERROR: outputfile failure");
	}
	if (pipe(fd) == -1)
	//here the pipe with its two files gets created
		exec_failed("ERROR: unsuccessful creation of pipe");
	pid = fork();
	if (pid == -1)
	exec_failed("ERROR: unsuccessful fork execution");
	if (pid == 0) {
		dup2(in, STDIN_FILENO);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		//i dont use read_end i just redirect out to read_end
		close(fd[WRITE_END]);
		cp_exec(argv[2], envp);
		//redirecting correctly!
		//child execve whileloop
	}
//need to also close mains fd's
//	close(fd[READ_END]);
	//not after wait?
/* instead of else for the parent
	we can just waitpid(pid, NULL, 0); 
	...
*/
	child_status();
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(out, STDOUT_FILENO);
	cp_exec(argv[3], envp);
// 		//redirecting correctly!
// 		//parent execve whileloop
		// wait(&wait_status);
// 	else {
		//it writes the cpid to to the int wait_status
		// if (WIFEXITED(wait_status))
		//WIFEXITED checks that it exits
		// {
		// 	status_code = WEXITSTATUS(wait_status);
			//if (WEXITSTATUS(wait_status) == 0)
				//what then?? (success)
			//WEXITSTATUS checks with what it exited
		// }
		// printf("Child process' wait_status and exit status: %d %d\n", wait_status, status_code);
}

int	child_status(void)
{
	int		wait_status;
	int		status_code;
	
	wait(&wait_status);
	if (WIFEXITED(wait_status))
		status_code = WEXITSTATUS(wait_status);
		return (status_code);
	return (0);
}

/*	open filedescriptors for in and out
	split the command string
	redirect stdin and stdout execve
	execve takes the command path, the command, and envp
*/
