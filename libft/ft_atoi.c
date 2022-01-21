/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:48:34 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/08 21:32:14 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		counter;
	long	output;
	int		sign;

	counter = 0;
	output = 0;
	sign = 1;
	while (str[counter] == 32 || (str[counter] <= 13 && str[counter] >= 9))
		counter++;
	if (str[counter] == '-')
	{
		sign = -1;
		counter++;
	}
	else if (str[counter] == '+')
		counter++;
	while (str[counter] >= '0' && str[counter] <= '9')
	{
		output = output * 10 + str[counter++] - '0';
		if (sign == -1 && output > (long) INT_MAX + 1)
			return (0);
		else if (sign == 1 && output > INT_MAX)
			return (-1);
	}
	return (sign * output);
}
