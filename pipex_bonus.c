/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:26:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/04 00:32:53 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	redirecting_child(t_data *data, char *cmd, char **envp)
{
	int	error;
	
	error = (
		close(data->out)
		||dup2(data->in, STDIN_FILENO) == -1
		||close(data->in)
		|| close(data->fd[READ_END]) == -1
		|| dup2(data->fd[WRITE_END], STDOUT_FILENO) == -1
		|| close(data->fd[WRITE_END]) == -1
	);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

int	redirecting_pipe(t_data *data, char *cmd, char **envp)
{
	int	error;
	
	error = (
	close(data->out)
	|| dup2(data->tmp_fd, STDIN_FILENO) == -1
	|| close(data->fd[READ_END]) == -1
	|| close(data->tmp_fd) == -1
	//ich muss alle verbindungen schliessen 
	//mit denen ich nichts mehr machen muss
	|| dup2(data->fd[WRITE_END], STDOUT_FILENO) == -1
	|| close(data->fd[WRITE_END]) == -1
	);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}


int	redirecting_parent(t_data *data, char *cmd, char **envp)
{
	int	error;
	
	error = (
	close(data->fd[WRITE_END]) == -1
	|| dup2(data->fd[READ_END], STDIN_FILENO) == -1
	|| close(data->fd[READ_END]) == -1
	|| dup2(data->out, STDOUT_FILENO) == -1
	|| close(data->out)== -1
	);
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

int	first_command(t_data *data, char *first_cmd, char **envp)
{
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_child(&data, first_cmd, envp);
	data->amount_cmd--;
	return(data->amount_cmd);
}

int	multiple_commands(t_data *data, char *cmd, char **envp)
{
	
	data->tmp_fd = data->fd[READ_END];
	close(data->fd[WRITE_END]);
	close(data->fd[READ_END]);
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_pipe(&data, cmd, envp);
	close(data->tmp_fd);
	data->amount_cmd--;
	return(data->amount_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	
	if (argc >= 5)
		exec_failed("ERROR: incorrect parameter number");
	data.in = open(argv[1], O_RDONLY);
	if (data.in == -1)
		exec_failed("ERROR: open infile failure");
	data.out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data.out == -1)
	{
		close(data.in);
		exec_failed("ERROR: open outfile failed");
	}
	data.amount_cmd = argc - 3;
	// -3 == pipex infile outfile
	i = 0;
	while (data.amount_cmd > 1)
	//oder 1? bis man halt nur noch 1 command drin aht dann rausspringen!
	//not sure if that works
	{
		if (data.amount_cmd == argc - 3)
		//wenn	wir noch alle ahben fangen wir ganz normal
		//in child redirect mit dem ersten command an
		{
			first_command(&data, argv[2], envp);
			close(data.in);
			//damit ich das nicht in jedem neun child schliessen uss
			//out muss fur den schluss beibehalten werden
			data.amount_cmd--;
		}
		else
			data.amount_cmd = multiple_commands(&data, argv[2 + i], envp);
		child_status();
		i++;
	}
	redirecting_parent(&data, argv[2 + i], envp);
}
