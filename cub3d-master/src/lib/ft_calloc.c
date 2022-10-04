/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:26:35 by cleticia          #+#    #+#             */
/*   Updated: 2022/09/04 00:55:52 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	t;

	t = (count * size);
	p = (char *) malloc(t);
	if (p == NULL)
		return (0);
	ft_bzero(p, t);
	return (p);
}
