/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:22:01 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/07 12:24:55 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n && ((unsigned char *)s)[counter] != ((unsigned char) c))
	{
		counter++;
	}
	if (counter == n)
	{
		return (NULL);
	}
	return (((void *)(s + counter)));
}
