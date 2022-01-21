/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 17:15:22 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/23 09:48:15 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	counter;

	counter = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[counter] != '\0')
	{
		f(counter, &s[counter]);
		counter++;
	}
}
