/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/09 08:14:37 by lfranca-         ###   ########.fr       */
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

/*
** save_map() armazena o conteúdo do mapa na matriz da estrutura principal
** antes disso, porém, verifica se os caminhos das texturas e os códigos rgb
** já estão armazenados na estrutura (ou seja, já "passamos" por eles no arquivo).
** Caso não, ele retorna erro e exita, porque faz parte das regras que o mapa
** deva ser O ULTIMO conteudo do arquivo (e tambem há a possibilidade de nem ter
** caminhos de texturas e/ou codigos rgb).
*/
static void save_map(t_map *map, int *content, char *line)
{
	if ((*content) == 0 && (!map->textures.east_wall || !map->textures.west_wall
			|| !map->textures.south_wall || !map->textures.north_wall
				|| !map->ceilling || !map->floor))
					invalid_rgb(line, NULL, map);
	map->monitoring = 0;
	map->map[*content] = ft_strdup(line);
	(*content)++;
}

/*
** store_file_content() irá abrir o arquivo onde estão os caminhos para
** as texturas, os códigos rgb e o mapa e irá percorrer esse conteúdo,
** separando-os e armazenando-os em variáveis na estrutura principal.
** Usa para isso as funções de apoio:
** - save_textures_rgb()
** - save_map()
*/
int	store_file_content(char **line, t_map *map, char *filename)
{
	int		ret;
	int content;

	ret = 1;
	content = 0;
	map->fd = open(filename, O_RDONLY);
	while (ret)
	{
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0)
			return (303);
		if (ft_strlen((*line)) != 0
			&& ((is_texture_path(*line)) || is_rgb_color(*line)))
			save_textures_rgb((*line), map);
		else if(is_empty_line(*line) && (map->monitoring == 6)) //ignorar linha vazia antes do mapa
		{
			free(*line);
			continue;
		}
		else
			save_map(map, &content, (*line));
        free(*line);
	}
	return (0);
}

void    check_textures_rgb(char *line, int *monitoring)
{
	static int  texture;
	static int  rgb;

	if (ft_strchr(line, '.')) //texturas
	{
		texture++;
		if (texture == TEXTURES_DONE)
			(*monitoring) += 4;
	}
	else if (ft_strchr(line, ','))//floor e ceilling
	{
		rgb++;
		if(rgb == RGB_DONE)
			(*monitoring ) += 2;//significa que passou pelo rgb
	}
}

int    count_height_width(char *line, t_map *map)
{
	int		size;

	if (map->monitoring != 6)
	{
		free(line);
		return (505); //wrong formating
	}
	map->height++;
	size = ft_strlen(line);
	if(size > map->width)
		map->width = size;
	return (0);
}

/*
** measure_height() vai tirar a altura da matriz do mapa (que servirá para o minimapa e
** para projetar o mapa 3d tambem).
*/
int	measure_height(char **line, t_map *map)
{
	int		ret;

	ret = 1;
	while (ret)
	{
        if (line && (*line))
            free(*line);
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0 && map->monitoring == 0)
			return (505);
 		if (ft_strchr(*line, '.') || ft_strchr(*line, ','))
            check_textures_rgb(*line, &map->monitoring);
		else if(is_empty_line(*line) && map->height == 0)
			continue;
		else if (count_height_width(*line, map) == 505)
			return (505);
	}
	if (*line)
		free(*line);
	if (map->height == 0)
	{
		close(map->fd);
		return (505);
	}
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