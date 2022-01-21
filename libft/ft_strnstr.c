/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:24:01 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/27 18:42:03 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	counter;

	counter = 0;
	if (*substr == '\0')
		return ((char *)str);
	while (str[counter] != '\0' && (ft_strlen(substr) <= len - counter))
	{
		if (ft_strncmp(&str[counter], substr, ft_strlen(substr)) == 0)
			return ((char *)&str[counter]);
		counter++;
	}
	return (NULL);
}
