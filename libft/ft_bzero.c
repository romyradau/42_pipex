/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:45:51 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/07 11:56:41 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n)
	{
		((char *)s)[counter] = '\0';
		counter++;
	}
}
