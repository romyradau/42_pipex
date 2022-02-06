/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:28:00 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/06 19:02:23 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
#include <stdio.h>


# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

typedef struct s_data{
	int		in;
	int		out;
	int		heredoc;
	char	*LIMITER;
	int		fd[2];
	int		tmp_fd;
	pid_t	pid;
	int		amount_cmd;
}	t_data;

int		redirecting_parent(t_data *data, char *cmd, char **envp);
int		redirecting_pipe(t_data *data, char *cmd, char **envp);
int		redirecting_first_command(t_data *data, char *cmd, char **envp);
void	child_status(void);
void	cmd_exec(char *cmd, char **envp);
void	free_split(char **split);
void	exec_failed(char *s);
int		handle_heredoc(t_data *data);
int		heredoc_commands(t_data *data, int argc, char **argv, char **envp);
int		first_command(t_data *data, char *first_cmd, char **envp);
int		multiple_commands(t_data *data, char *cmd, char **envp);



#endif