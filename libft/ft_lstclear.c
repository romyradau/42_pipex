/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:57:47 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/24 18:10:47 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*temporary;

	while (*lst != NULL)
	{
		temporary = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temporary;
	}
	*lst = NULL;
}
