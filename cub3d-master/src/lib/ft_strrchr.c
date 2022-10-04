/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:32:55 by cleticia          #+#    #+#             */
/*   Updated: 2022/09/04 05:06:12 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char    *ft_strrchr(const char *s, int c)
{
    size_t    leng;

    leng = ft_strlen(s);
    while (leng)
    {
		printf("printando o charactere %c\n", s[leng]);
        if (s[leng] == (unsigned char)c)
            return ((char *)&s[leng]);
        leng--;
    }
	printf("cheguei aqui na strrchr 2\n");
    if (s[leng] == (unsigned char)c)
        return ((char *)&s[leng]);
    return (NULL);
}

/*


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

*/

