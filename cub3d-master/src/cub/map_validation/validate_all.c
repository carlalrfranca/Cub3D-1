/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:36 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/14 20:45:04 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_char_border_or_empty_line(char **map_line, int char_counter)
{
	if (char_counter == 0
		|| char_counter == ((int)ft_strlen(map_line[0]) - 1))
		return (1);
	if (is_empty_line(map_line[0]) || is_empty_line(map_line[-1])
		|| is_empty_line(map_line[1]))
		return (1);
	return (0);
}

/*
** Libera:
** - caminhos das texturas (se houver)
** - Matriz de caracteres (mapa em caracteres extraido do arquivo)
** - Os códigos rgb (se houver)
** - A estrutura principal (map)
*/
void	free_map(t_map *map)
{
	int	index;

	index = -1;
	free_textures(map);
	if (map->map[0] != NULL && map->height > 0)
	{
		while (++index < map->height)
			free (map->map[index]);
	}
	free (map->map);
	if (map->floor)
		free (map->floor);
	if (map->ceilling)
		free (map->ceilling);
	free (map);
	map = NULL;
}

void	map_error(t_map *map)
{
	free_map(map);
	write(2, "Error\nInvalid Map\n", 18);
	exit(11);
}

void	free_matrix(char **split_values)
{
	int	counter;

	counter = 0;
	while (split_values[counter])
	{
		free(split_values[counter]);
		counter++;
	}
}

/*
** Validará as strings de rgb, as texturas
** e, se tudo estiver correto, redirecionará para a verificação do mapa
** (se está devidamente cercado de paredes e paredes internas
** não estão como "células solitárias"/paredes "flutuando"
** entre 'zeros').
*/
int	validate_map(t_map *map)
{
	if (validate_rgb(map->floor) != 0)
	{
		free_map(map);
		file_error("Error\nRGB must be: [0-255],[0-255],[0-255]", 2);
	}
	if (validate_rgb(map->ceilling) != 0)
	{
		free_map(map);
		file_error("Error\nRGB must be: [0-255],[0-255],[0-255]", 2);
	}
	validate_texture(map);
	is_map_open(map);
	if (map->spawing == 0)
		map_error(map);
	return (0);
}
