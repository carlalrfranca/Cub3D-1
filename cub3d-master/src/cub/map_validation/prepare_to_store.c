/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/09 11:13:17 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/*
** Verifica se a linha lida é correspondente a uma "linha vazia" (ou porque só
** tem o caracter nulo ou porque tem espaços/tabs mas mais nada. É por isso
** que trimá-la faz parte do processo de verificação também. Afinal, caso ela
** tenha "conteúdo" - espaços e/ou tabs - se for só isso, ela ainda deve ser
** considerada vazia).
** É importante fazer essa verificação porque, caso seja uma linha vazia
** ANTES DO MAPA, podemos "pular ela" - continuar para a próxima
** iteração/linha.
*/
int is_empty_line(char *line)
{
	char *trimmed_line;

	trimmed_line = NULL;
	if (ft_strlen(line) == 0)
		return (1);
	trimmed_line = ft_strtrim(line, " \t");
	if (ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return (1);
	}
	free(trimmed_line);
	return (0);
}

static void init_map(t_map *map)
{
	map->map = NULL;
	map->floor = NULL;
	map->ceilling = NULL;
	map->monitoring = 0;
	map->height = 0;
	map->width = 0;
	map->fd = 0;
	map->spawing = 0;
	map->is_squared_map = 1;
	map->textures.east_wall = NULL;
	map->textures.west_wall = NULL;
	map->textures.north_wall = NULL;
	map->textures.south_wall = NULL;
}

static void alloc_zero_map(t_map *map)
{
	int counter;

	counter = 0;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	while (counter < map->height)
	{
		map->map[counter] = NULL;
		counter++;
	}
	map->map[map->height] = NULL;
}

t_map	*prepare_to_store(char *filename)
{
	t_map	*map;
	char	*line;

	line = NULL;
	map = malloc(sizeof(t_map));
	init_map(map);
	map->fd = open(filename, O_RDONLY);
	if (map->fd == -1)
	{
		free(map);
        file_error("Error\nFailed to open map file.", 5);
	}
	if (measure_height(&line, map) == 505)
	{
		free(map);
		file_error("Error\nEmpty file or Map must on the end of file", 505);
	}
	alloc_zero_map(map);
	if (store_file_content(&line, map, filename) == 303)
		map_error(map);
	close(map->fd);
	return (map);
}


/*
./cub3d ./src/maps/map.cub
./cub3d ./src/maps/map3.cub
*/