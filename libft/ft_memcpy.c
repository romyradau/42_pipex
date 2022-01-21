/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 08:25:59 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/08 21:23:47 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	counter;

	counter = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	while (counter < n)
	{
		((char *) dst)[counter] = ((char *) src)[counter];
		counter++;
	}
	return (dst);
}
