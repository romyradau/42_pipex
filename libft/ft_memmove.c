/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:23:51 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/07 13:08:36 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
	{
		while (len > 0)
		{
			((char *) dst)[len - 1] = ((char *) src)[len - 1];
			len--;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
