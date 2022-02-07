/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:16:00 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/07 17:52:01 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	redirecting_first_command(t_data *data, char *cmd, char **envp)
{
	int	error;
	
	if (data->heredoc)
		data->in = open("./tmp_file", O_RDONLY, 0644);
	
	error = (
		close(data->out) == -1
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
	close(data->out) == -1
	|| dup2(data->tmp_fd, STDIN_FILENO) == -1
	|| close(data->fd[READ_END]) == -1
	|| close(data->tmp_fd) == -1
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
	pause();
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

/*
lsof -c pipex
beim letzte mal muss die exec noch aus dem STDIN_FILENO lesen
*/