/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:21:17 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/27 18:41:43 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	end;
	size_t	counter;
	size_t	len;

	len = ft_strlen(dst) + ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	end = 0;
	while (dst[end] != '\0')
		end++;
	counter = 0;
	while (src[counter] != '\0' && counter + end < dstsize - 1)
	{
		dst[end + counter] = src[counter];
		counter++;
	}
	dst[end + counter] = '\0';
	return (len);
}
