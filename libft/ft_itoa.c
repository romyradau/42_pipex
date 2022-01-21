/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:02:10 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/21 22:34:31 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long n)
{
	long	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	end;
	long	number;

	i = 0;
	end = ft_count(n);
	number = n;
	str = ft_calloc((ft_count(number) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (number < 0)
	{
		str[0] = '-';
		i++;
	}
	while (i < end)
	{
		if (number < 0)
			number *= -1;
		str[end - 1] = number % 10 + 48;
		number /= 10;
		end--;
	}
	return (str);
}
