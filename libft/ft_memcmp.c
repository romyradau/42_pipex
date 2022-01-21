/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:11:54 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/07 12:45:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			counter;
	unsigned char	a;
	unsigned char	b;

	counter = 0;
	while (1)
	{
		if (counter == n)
		{
			return (0);
		}
		if (((unsigned char *) s1)[counter] != ((unsigned char *) s2)[counter])
		{
			a = ((unsigned char *) s1)[counter];
			b = ((unsigned char *) s2)[counter];
			return (a - b);
		}
		counter++;
	}
}
