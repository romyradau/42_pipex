/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 11:24:02 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/24 15:00:40 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_element;

	last_element = NULL;
	while (lst != NULL)
	{
		last_element = lst;
		lst = lst->next;
	}
	return (last_element);
}
