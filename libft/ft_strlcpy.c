/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:00:02 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/27 18:41:50 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	counter;

	counter = 0;
	if (src == 0)
		return (0);
	if (dstsize > 0)
	{
		while (counter < dstsize - 1 && src[counter] != '\0')
		{	
			dst[counter] = src[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (ft_strlen(src));
}
