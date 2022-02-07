/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:12:15 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/07 17:48:34 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

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

void	handle_heredoc(t_data *data)
{
	char	*line;
	char	*test;
	int		line_length;

	line_length = 1;
	while (line_length)
	{
		line = get_next_line(0);
		if (!line)
			exec_failed("ERROR: missing here_doc input");
		line_length = ft_strlen(line);
		test = ft_strtrim(line, "\n");
		if (!ft_strncmp(test, data->LIMITER, ft_strlen(data->LIMITER) + 1))
		{
			free(test);
			free(line);
			return ;
		}
		write(data->heredoc, line, line_length);
		free(test);
		free(line);
	}
}
