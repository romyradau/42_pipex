/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:00:29 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/27 18:42:38 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	counter;

	counter = 0;
	while (s[counter] != '\0')
		counter++;
	if (s[counter] == (char)c)
		return ((char *)&s[counter]);
	while (s[counter] != (char)c && counter > 0)
		counter--;
	if (s[counter] == (char)c)
		return ((char *)&s[counter]);
	return (NULL);
}
