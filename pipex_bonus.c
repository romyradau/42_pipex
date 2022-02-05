/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:26:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/05 19:49:39 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_command(t_data *data, char *first_cmd, char **envp)
{
	if (pipe(data->fd) == -1)
		exec_failed("ERROR: unsuccessful creation of pipe");
	data->pid = fork();
	if (data->pid == -1)
		exec_failed("ERROR: unsuccessful fork execution");
	if (data->pid == 0)
		redirecting_child(data, first_cmd, envp);
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
	
	data->amount_cmd = argc - 4;
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
//!!für heredoc mussen die argv zahlen verandert werden!!!
//im not really doing sth with wait am i ?

int	handle_here_doc(t_data *data)
{
	char	*line;
	int		line_length;

	line_length = 1;
	while (line_length)
	{
		line = get_next_line(0);
		if (!line)
			exec_failed("ERROR: missing here_doc input");
		line_length = ft_strlen(line);
		if (!ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)))
			return (data->heredoc);
		//uberpruft der jetzt auch wirklich genau nur das wort?
		write(data->heredoc, line, line_length);
		//muss da noch ne new line hin?
		free(line);

	}
	return(data->heredoc);
	//oder muss ich data zurückgeben, damit das auch alles ubernommen wird?
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	if (argc < 5)
		exec_failed("ERROR: incorrect parameter number");
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		data.heredoc = open("./tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
		data.LIMITER = argv[2];
		data.in = data.heredoc;
		//muss ich hier eig dup verwenden?
	}
	//muss ich hier noch bullshit input handlen?
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
	redirecting_parent(
			&data, argv[2 + pipe_commands(&data, argc, argv, envp)], envp);
}
