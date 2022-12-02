/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/02 01:04:35 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int  is_texture_path(char *line)
{
    if (ft_strncmp("NO", line, 2) == 0 || ft_strncmp("SO", line, 2) == 0
        || ft_strncmp("WE", line, 2) == 0 || ft_strncmp("EA", line, 2) == 0)
            return (1);
    return (0);
}

static void save_texture(t_image *textures, char *line) //TRIMMAR AQUI TAMBEM
{
    if(ft_strncmp("NO .", line, 4) == 0)
		textures->north_wall = ft_strdup(ft_strchr(line, '.'));		
	else if(ft_strncmp("SO .", line, 4) == 0)
		textures->south_wall = ft_strdup(ft_strchr(line, '.'));	
	else if(ft_strncmp("WE .", line, 4) == 0)
		textures->west_wall = ft_strdup(ft_strchr(line, '.'));
	else if(ft_strncmp("EA .", line, 4) == 0)
		textures->east_wall = ft_strdup(ft_strchr(line, '.'));
}

static int is_rgb_color(char *line)
{
    if (ft_strncmp("F", line, 1) == 0)
        return (1);
    else if (ft_strncmp("C", line, 1) == 0)
        return (2);
    return (0);
}

static char *save_rgb_code(char *line)
{
    char    *rgb_color;
    char    *trimmed;
    char    *rgb_trimmed;

    rgb_color = NULL;
    trimmed = ft_strtrim(line, " ");
    rgb_color = ft_strchr(trimmed, ' ');
    if (!rgb_color)
    {
        free(trimmed);
        return (NULL);
    }
    //trim again just so we garantee there's no extra spaces between the character and the number
    rgb_trimmed = ft_strtrim(rgb_color, " ");
    free(trimmed);
    return (rgb_trimmed);

}

static void invalid_rgb(char *line, char *rgb_to_free, t_map *map)
{
    if(map->map)
        free(map->map);
    free(map);
    write(2, "Error\nInvalid Map: RGB Formating.\n", 34);
    free(line);
	if(rgb_to_free)
	    free(rgb_to_free);
	exit(10);
}

static void check_which_rgb(char *line, char **floor, char **ceilling, t_map *map)
{
    if (is_rgb_color(line) == 1)
	{
        (*floor) = save_rgb_code(line);
        if ((*floor) == NULL)
           invalid_rgb(line, (*ceilling), map);
	}
	else if (is_rgb_color(line) == 2)
	{
		(*ceilling) = save_rgb_code(line);
        if ((*ceilling) == NULL)
            invalid_rgb(line, (*floor), map);
	}
}

void	store_map(char **line, t_map *map, char *filename)
{
	int		content;
	int		ret;

	content = 0;
	ret = 1;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	map->map[map->height] = NULL;
	map->fd = open(filename, O_RDONLY);
	while (ret)
	{
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0)
			file_error("Error\nEmpty map.", 5);
        if(is_texture_path(*line))
            save_texture(&map->textures, *line);
        else if (is_rgb_color(*line))
            check_which_rgb(*line, &map->floor, &map->ceilling, map);
		else if(ft_strlen(*line) == 0 && (map->monitoring == 6)) //ignorar linha vazia antes do mapa
		{
			free(*line);
			continue;
		}
		else
		{ //caso for o mapa
            //colocar uma restrição aqui porque as texturas e o rgb tem que já ter vindo
			map->monitoring = 0;
			map->map[content] = ft_strdup(*line);
			content++;
		}
        free(*line);
	}
}

void	measure_height(char **line, t_map *map)
{
	int		size;
	int		ret;
	int		texture;
	int		rgb;
	int		monitoring;

	ret = 1;
	rgb = 0;
	texture = 0;
	monitoring = 0;
	while (ret)
	{
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0)
			file_error("Error\nEmpty file.", 5); //monitoring_content();
		if (ft_strchr(*line, '.')) //texturas
		{
			texture++;
			if (texture == TEXTURES_DONE) //precisa juntar ao caso de se o rgb vier ANTES (algum calculo com os valores?)
				monitoring += 4;
		}
		else if (ft_strchr(*line, ','))//floor e ceilling
		{
			rgb++;
			if(rgb == RGB_DONE)
				monitoring += 2;//significa que passou pelo rgb
		}
		else if(ft_strlen(*line) == 0 && map->height == 0)//se nao é linha vazia e nao é 2
		{
			free(*line);
			continue;
		}
		else if (monitoring == 6) //significa que ja passamos tanto pelas texturas quanto pelo rgb e só resta o mapa
		{
			map->height++;
			size = ft_strlen(*line);
			if(size > map->width)
				map->width = size;
		}
		if (*line)
			free(*line);
	}
	if (map->height == 0)
	{
		close(map->fd);
		file_error("Error\nEmpty map.", 5);
	}
	map->monitoring = monitoring;
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
	measure_height(&line, map);
	store_map(&line, map, filename);
	close(map->fd);
	return (map);
}

/*
./cub3d ./src/maps/map.cub
./cub3d ./src/maps/map3.cub
*/