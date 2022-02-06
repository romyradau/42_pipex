
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:48:26 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/05 17:24:02 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search(char *s, char c)
{
	int	nl;

	nl = 0;
	if (s == NULL)
		return (-1);
	if (c == '\0')
	{
		while (s[nl] != '\0')
			nl++;
		return (nl);
	}
	while (s[nl] != '\0')
	{
		if (s[nl] == c)
			return (nl);
		nl++;
	}
	return (-1);
}

char	*output_function(char	**pot, ssize_t bytes)
{
	char	*output;

	if (*pot)
	{
		if (**pot == '\0' && bytes <= 0)
		{
			free(*pot);
			return (NULL);
		}
	}
	if (search (*pot, '\n') == -1)
	{
		output = my_substr(*pot, 0, search(*pot, '\0'));
		my_free(pot);
	}
	else
		output = output_extension(pot);
	return (output);
}

char	*output_extension(char	**pot)
{
	char	*output;
	char	*temp;
	size_t	next_char;

	if (search(*pot, '\n') == 0)
		output = my_substr(*pot, 0, 1);
	else
		output = my_substr(*pot, 0, search(*pot, '\n') + 1);
	next_char = (search(*pot, '\n') + 1);
	temp = my_substr(*pot, next_char, my_strlen(next_char, *pot));
	my_free(pot);
	*pot = temp;
	return (output);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes;
	char		*buf;
	static char	*pot;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	buf = NULL;
	while (search(pot, '\n') < 0)
	{
		buf = my_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buf == NULL)
			return (NULL);
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		pot = my_strjoin(pot, buf);
		my_free(&buf);
	}
	my_free(&buf);
	return (output_function(&pot, bytes));
}
