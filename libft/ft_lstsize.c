/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 10:55:28 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/24 13:24:52 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list	*lst)
{
	int	quantity;

	quantity = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		quantity++;
		lst = lst->next;
	}
	return (quantity);
}
