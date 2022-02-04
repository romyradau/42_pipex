/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:16:00 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/04 19:14:42 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	redirecting_child(t_data *data, char *cmd, char **envp)
{
	int	error;
	
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
	if (error == 0)
		cmd_exec(cmd, envp);
	return (error);
}

/*
pause();
lsof -c pipex
beim letzte mal muss die exec noch aus dem STDIN_FILENO lesen
*/