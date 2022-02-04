/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:28:00 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/04 17:22:48 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

typedef struct s_data{
	int		in;
	int		out;
	int		fd[2];
	int		tmp_fd;
	pid_t	pid;
	int		amount_cmd;
}	t_data;

int		redirecting_parent(t_data *data, char *cmd, char **envp);
int		redirecting_pipe(t_data *data, char *cmd, char **envp);
int		redirecting_child(t_data *data, char *cmd, char **envp);
void	child_status(void);
void	cmd_exec(char *cmd, char **envp);
void	free_split(char **split);
void	exec_failed(char *s);

#endif