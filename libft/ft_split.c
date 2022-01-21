/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:39:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/20 20:03:56 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_ptr_quantity(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	t_split	split;

	split.index = 0;
	split.start = 0;
	if (s == NULL)
		return (NULL);
	split.ptr_quanity = ft_ptr_quantity(s, c);
	split.ptrptr = ft_calloc((split.ptr_quanity + 1), sizeof(char *));
	if (split.ptrptr == NULL)
		return (NULL);
	while (split.index != split.ptr_quanity)
	{
		while (s[split.start] != '\0' && s[split.start] == c)
			split.start++;
		split.end = split.start;
		while (s[split.end] != '\0' && s[split.end] != c)
			split.end++;
		split.ptrptr[split.index] = ft_substr(s, split.start,
				(split.end - split.start));
		split.start = split.end;
		split.index++;
	}
	split.ptrptr[split.index] = NULL;
	return (split.ptrptr);
}

size_t	ft_ptr_quantity(char const *s, char c)
{
	size_t	counter;
	size_t	quantity;

	counter = 0;
	quantity = 0;
	if (s[0] == '\0')
		return (0);
	while (s[counter] != '\0')
	{
		if (s[counter] != c && (s[counter + 1] == c || s[counter + 1] == '\0'))
			quantity++;
		counter++;
	}
	return (quantity);
}
