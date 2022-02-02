/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:26:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/02 22:41:45 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	redirecting_child(t_data *data, char *cmd, char **envp)
{
	int	error;
	
	error = (
		dup2(data->in, STDIN_FILENO) == -1
		|| close(data->fd[READ_END]) == -1
		|| dup2(data->fd[WRITE_END], STDOUT_FILENO) == -1
		|| close(data->fd[WRITE_END]) == -1
	);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}
//if -1 success it will be 1
//close and dup2 error check

void	redirecting_parent(t_data *data, char *cmd, char **envp)
{
	close(data->fd[WRITE_END]);
	dup2(data->fd[READ_END], STDIN_FILENO);
	close(data->fd[READ_END]);
	dup2(data->out, STDOUT_FILENO);
	cmd_exec(cmd, envp);
}

//close and dup2 error check

int	first_command(t_data *data, char *argv, char **envp)
{
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_child(&data, argv[2], envp);
}

int	multiple_commands(t_data *data)
{
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
	
	data->amount_cmd++;
	return(data->amount_cmd);
}
//draw what happens!

int	main(int argc, char **argv, char **envp)
{
	int		in;
	int		out;
	t_data	data;

	if (argc >= 5)
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
	data.amount_cmd = argc - 3;
	// -3 == pipex infile outfile
	while (data.amount_cmd > 2)
	//oder 1? bis man halt nur noch 1 command drin aht dann rausspringen!
	//not sure if that works
	{
		if (data.amount_cmd == argc - 3)
		//wenn	wir noch alle ahben fangen wir ganz normal
		//in child redirect mit dem ersten command an
			first_command(&data, argv[2], envp);
			data.amount_cmd--;
		child_status();
		
		data.amount_cmd = multiple_commands(&data);
	}
	redirecting_parent(&data, argv[3], envp);
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
*/