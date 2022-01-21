/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:23:58 by rschleic          #+#    #+#             */
/*   Updated: 2021/07/24 19:34:06 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	(void)del;
	new_list = NULL;
	while (lst != NULL)
	{
		ft_lstadd_back(&new_list, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (new_list);
}
