/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 18:41:54 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/18 20:44:12 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	size_t	len;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	newstr = ft_calloc((len + 1), sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcat(newstr, s1, len + 1);
	ft_strlcat(newstr, s2, len + 1);
	return (newstr);
}
