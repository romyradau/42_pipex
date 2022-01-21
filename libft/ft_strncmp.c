/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:15:52 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/08 21:25:48 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	counter = 0;
	if (n == 0)
		return (0);
	while (counter + 1 < n && a[counter] != '\0' && a[counter] == b[counter])
		counter++;
	return (a[counter] - b[counter]);
}
