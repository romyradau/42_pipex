/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:39:42 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/02 20:54:46 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
}
//change for no bonus too!!!

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
		//when the path is not set 
		//i need to check anyways if its accessable
		// am schluss checken ob der command auch ohne path ausführbar ist 
	cmd_args = ft_split(cmd, ' ');
	find_path(paths, cmd_args, envp);
	free_split(paths);
	free_split(cmd_args);
	exec_failed("ERROR: no matching path found\n");
}

void	child_status(void)
{
	int		wait_status;
	int		status_code;

	wait(&wait_status);
	if (WIFEXITED(wait_status))
	{
		status_code = WEXITSTATUS(wait_status);
		if (status_code)
			exec_failed("ERROR: cp exit unsuccessful");
	}
}
/*
	return value of cp gets written to &wait_status
	if (WIFEXITED(wait_status))
		checks that cp exits
	if (WEXITSTATUS(wait_status) == 0)
		checks with what it exited
		0 == success
*/
