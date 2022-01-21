/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 18:16:07 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/18 20:54:58 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char	const *s, unsigned	int start, size_t len)
{
	char	*subs;
	size_t	counter;

	counter = 0;
	if (s == NULL)
		return (NULL);
	subs = malloc((len + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		subs[0] = '\0';
		return (subs);
	}
	while (counter < len)
		subs[counter++] = s[start++];
	subs[counter] = '\0';
	return (subs);
}
