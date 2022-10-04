/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:32:03 by cleticia          #+#    #+#             */
/*   Updated: 2022/09/04 01:01:45 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if ((unsigned char)c == *(s + i))
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((unsigned char)c == *(s + i))
	{
		return ((char *)s + i);
	}
	return (0);
}

