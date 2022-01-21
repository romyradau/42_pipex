/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:23:04 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/21 22:34:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_contains(char *set, char s1)
{
	size_t	counter;

	counter = 0;
	while (set[counter] != '\0')
	{
		if (set[counter] == s1)
			return (1);
		counter++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		counter;
	size_t		start;
	size_t		end;
	size_t		len_trims;
	char		*trims;

	counter = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[counter] != '\0' && ft_contains((char *)set, s1[counter]) != 0)
		counter++;
	start = counter;
	counter = ft_strlen(s1) - 1;
	while (counter > 0 && ft_contains((char *)set, s1[counter]) != 0)
		counter--;
	end = counter;
	len_trims = (end - start) + 1;
	if (end < start)
		len_trims = 1;
	trims = ft_substr(s1, start, len_trims);
	return (trims);
}
