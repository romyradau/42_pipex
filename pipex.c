/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:25:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/21 18:29:10 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>


void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);


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
	out = open(argv[4], O_RDWR | O_CREAT);
	if (out == -1)
	{
		close(in);
		exec_failed("ERROR: outputfile failure");
	}

	
	execve("/bin/cat", NULL, envp);
	//when to close in and out correctly??
	
	// handle_input();
	// int fd;

	// open("file", );
}


// "< Makefile cat | grep something > out"
// "./pipex file cmd cmd file"