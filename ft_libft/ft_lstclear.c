/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:04:38 by gghaya            #+#    #+#             */
/*   Updated: 2022/11/02 00:05:49 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		(*lst) = p;
	}
}
