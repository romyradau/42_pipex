/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:41:12 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/21 22:33:03 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	size_t	counter;

	counter = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	mapi = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (mapi == NULL)
		return (NULL);
	while (s[counter] != '\0')
	{
		mapi[counter] = f(counter, s[counter]);
		counter++;
	}
	mapi[counter] = '\0';
	return (mapi);
}
