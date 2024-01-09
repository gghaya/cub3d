/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:00:47 by gghaya            #+#    #+#             */
/*   Updated: 2022/11/01 23:10:48 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocation;

	allocation = malloc(count * size);
	if (allocation == 0)
		return (0);
	ft_bzero(allocation, count * size);
	return (allocation);
}
