/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:22:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/28 17:51:22 by rschleic         ###   ########.fr       */
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
	while (paths[i])
	{
		tmp_match = ft_strjoin(paths[i], "/");
		match = ft_strjoin(tmp_match, cmd_args[0]);
		free(tmp_match);
		if (access(match, F_OK) == 0)
			execve(match, cmd_args, envp);
		free(match);
		i++;
	}
}

void	cmd_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_args;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		exec_failed("PATH not set\n");
	paths = ft_split(envp[i] + 6, ':');
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
