/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:39:42 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/16 13:31:00 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	exec_failed(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	find_path(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*match;
	char	*tmp_match;

	i = 0;
	while (paths && paths[i])
	{
		tmp_match = ft_strjoin(paths[i], "/");
		match = ft_strjoin(tmp_match, cmd_args[0]);
		free(tmp_match);
		if (access(match, F_OK) == 0)
			execve(match, cmd_args, envp);
		free(match);
		i++;
	}
	if (access(cmd_args[0], F_OK) == 0)
		execve(cmd_args[0], cmd_args, envp);
	//das war dafur falls Path unsetted war, der cmd aber trzd valid ist
}

void	cmd_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_args;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 6, ':');
	cmd_args = ft_split(cmd, ' ');
	find_path(paths, cmd_args, envp);
	free_split(paths);
	free_split(cmd_args);
	exec_failed("ERROR: no matching path found\n");
}
