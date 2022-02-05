/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 20:16:54 by rschleic          #+#    #+#             */
/*   Updated: 2021/09/14 14:45:59 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(size_t start, char *str)
{
	while (str[start] != '\0')
		start++;
	return (start);
}

void	*my_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	counter;

	counter = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (counter != count)
	{
		ptr[counter] = 0;
		counter++;
	}
	return (ptr);
}

char	*my_strjoin(char	*pot, char	*buf)
{
	size_t	len;
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (pot == NULL)
		pot = my_substr("", 0, 0);
	len = my_strlen(i, pot) + my_strlen(j, buf);
	newstr = my_calloc((len + 1), sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (pot[i] != '\0')
	{
		newstr[i] = pot[i];
		i++;
	}
	while (i < len)
		newstr[i++] = buf[j++];
	if (pot != NULL)
		my_free(&pot);
	return (newstr);
}

char	*my_substr(char	*s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*subs;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	subs = malloc(sizeof(char) * (len + 1));
	if (subs == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			subs[j] = s[i];
			j++;
		}
		i++;
	}
	subs[j] = '\0';
	return (subs);
}

void	my_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
