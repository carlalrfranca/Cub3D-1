/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture_rgb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:50:13 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/09 18:14:48 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	validate_texture(t_map *map)
{
	if (map->textures.north_wall == 0 || map->textures.south_wall == 0
		|| map->textures.west_wall == 0 || map->textures.east_wall == 0)
		map_error(map);
}

static int	is_out_of_range(char **split_values, int i)
{
	int	rgb;

	rgb = 0;
	rgb = ft_atoi(split_values[i]);
	if (rgb < 0 || rgb > 255)
	{
		free_matrix(split_values);
		return (1);
	}
	return (0);
}

static int	is_code_numbers(char **split_values, int i)
{
	int	j;

	j = -1;
	while (split_values[i][++j])
	{
		if (ft_isdigit(split_values[i][j]) == -1)
		{
			free_matrix(split_values);
			return (606);
		}
	}
	return (0);
}

/*
** Verifica que o código rgb seja feito de digitos numericos,
** esteja dentro do range de 0-255 e tenha sido separado por
** virgulas (gerando 3 numeros, nao mais nem menos).
** Usa as funções de apoio acima:
** - is_code_numbers()
** - is_out_of_range()
*/
int	validate_rgb(char *rgb_value)
{
	char	**split_values;
	int		i;

	i = -1;
	split_values = ft_split(rgb_value, ',');
	while (split_values[++i])
	{
		if (is_code_numbers(split_values, i) == 606)
		{
			free(split_values);
			return (606);
		}
		if (is_out_of_range(split_values, i) == 1)
		{
			free(split_values);
			return (707);
		}
	}
	free_matrix(split_values);
	free (split_values);
	if (i != 3)
		return (808);
	return (0);
}
