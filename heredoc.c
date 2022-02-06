/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:12:15 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/06 19:06:16 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	heredoc_commands(t_data *data, int argc, char **argv, char **envp)
{
	int		i;
	
	data->amount_cmd = argc - 4;
	i = 0;
	while (data->amount_cmd > 1)
	{
		if (data->amount_cmd == argc - 4)
		{
			
			first_command(data, argv[3], envp);
			close(data->in);
			data->amount_cmd--;
		}
		else
		{
			data->amount_cmd = multiple_commands(data, argv[3 + i], envp);
			data->amount_cmd--;
		}
		child_status();
		i++;
	}
	return (i);
}

int	handle_heredoc(t_data *data)
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
		//nein bullshit handeln!
		write(data->heredoc, line, line_length);
		//muss da noch ne new line hin?
		free(line);

	}
	return(data->heredoc);
	//oder muss ich data zurückgeben, damit das auch alles ubernommen wird?
	//sollte ieg void sein
}