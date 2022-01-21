/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 14:32:02 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/24 15:10:19 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (ft_lstlast(*lst) == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
