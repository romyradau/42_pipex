/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:12:15 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/05 19:29:35 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	handle_here_doc(t_data *data)
{
	char	*line;
	int		line_length;

	line_length = 1;
	while (line_length)
	//while(1)
	{
		line = get_next_line(0);
		if (!line)
			exec_failed("ERROR: missing here_doc input");
		line_length = ft_strlen(line);
		if (!ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)))
			return (data->heredoc);
		write(data->heredoc, line, line_length);
		free(line);
		//geht gar nicht wenn ich des auf de stack habe am anfang
		//passt die stelle?
		//weil wenn cihs unten mache habe ich doch wider schwierigkeiten ind ie while zu kommen?
	//uberpruft der jetzt auch wirklich genau nur das wort?
		//muss da noch ne new line hin?
	//chek if da uberhaupt was drin steht
	//aber man muss beim ersten mal trzd rein
	}
	return(data->heredoc);
	//oder muss ich data zurückgeben, damit das auch alles ubernommen wird?
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	if (argc < 5)
		exec_failed("ERROR: incorrect parameter number");
	if (ft_strncmp(!argv[1], "here_doc", 8))
	{	
		data.heredoc = open("./tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
		data.LIMITER = argv[2];
		data.in = handle_here_doc(&data);
	}
		//passt das so dass ich einfach n int da rein speichere?
	// data.in = open(argv[1], O_RDONLY);
	//orgeneienn fd offnen 
	//dann da mit gnl reinschreiben

	// if (data.in == -1)
	// 	exec_failed("ERROR: open infile failure");
	data.out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data.out == -1)
	{
		close(data.in);
		exec_failed("ERROR: open outfile failed");
	}
	redirecting_parent(
			&data, argv[2 + pipe_commands(&data, argc, argv, envp)], envp);
}
