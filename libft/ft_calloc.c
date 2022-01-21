/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:45:48 by rschleic          #+#    #+#             */
/*   Updated: 2022/01/20 19:58:32 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	counter;
	void	*ptr;

	counter = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		ft_putendl_fd("ERROR: malloc failed", 2);
		exit(1);
	}
	while (counter < count * size)
	{
		((char *)ptr)[counter] = 0;
		counter++;
	}
	return (ptr);
}
