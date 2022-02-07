/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:26:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/07 16:12:38 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	first_command(t_data *data, char *first_cmd, char **envp)
{
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_first_command(data, first_cmd, envp);
	return(data->amount_cmd);
}

int	multiple_commands(t_data *data, char *cmd, char **envp)
{
	data->tmp_fd = dup(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	close(data->fd[READ_END]);
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_pipe(data, cmd, envp);
	close(data->tmp_fd);
	return(data->amount_cmd);
}

//close errors check

int	pipe_commands(t_data *data, int argc, char **argv, char **envp)
{
	int		i;
	
	data->amount_cmd = argc - 3;
	i = 0;
	while (data->amount_cmd > 1)
	{
		if (data->amount_cmd == argc - 3)
		{
			first_command(data, argv[2], envp);
			close(data->in);
			data->amount_cmd--;
		}
		else
		{
			data->amount_cmd = multiple_commands(data, argv[2 + i], envp);
			data->amount_cmd--;
		}
		child_status();
		i++;
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	if (argc < 5)
		exec_failed("ERROR: incorrect parameter number");
	if (!ft_strncmp(argv[1], "here_doc\0", 9))
	{
		data.heredoc = open("./tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (data.heredoc == -1)
			exec_failed("ERROR: open tmp_file failure");
		data.LIMITER = argv[2];
		handle_heredoc(&data);
		if (close(data.heredoc) == -1)
			exec_failed("ERROR: heredoc didn't close properly");
	}
	else
		data.in = open(argv[1], O_RDONLY);
	if (data.in == -1)
		exec_failed("ERROR: open infile failure");
	data.out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data.out == -1)
	{
		close(data.in);
		exec_failed("ERROR: open outfile failed");
	}
	if ((!ft_strncmp(argv[1], "here_doc\0", 9)))
		redirecting_parent(
				&data, argv[3 + heredoc_commands(&data, argc, argv, envp)], envp);
	redirecting_parent(
			&data, argv[2 + pipe_commands(&data, argc, argv, envp)], envp);
}
