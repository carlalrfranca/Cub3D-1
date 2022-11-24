/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/24 03:49:33 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	store_map(char **line, t_map *map, char *filename)
{
	char	*to_trim;
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
			file_error();
		if (ft_strncmp("NO .", *line, 4) == 0)
			map->textures.north_wall = ft_strchr(*line, '.');		
		else if (ft_strncmp("SO .", *line, 4) == 0)
			map->textures.south_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("WE .", *line, 4) == 0)
			map->textures.west_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("EA .", *line, 4) == 0)
			map->textures.east_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("F", *line, 1) == 0)
		{
			map->floor = ft_strchr(*line, ' ');
			to_trim = map->floor;
			map->floor = ft_strtrim(to_trim, " ");
			to_trim = NULL;
		}
		else if (ft_strncmp("C", *line, 1) == 0)
		{
			map->ceilling = ft_strchr(*line, ' ');
			to_trim = map->ceilling;
			map->ceilling = ft_strtrim(to_trim, " ");
			to_trim = NULL;
		}
		else if(ft_strlen(*line) == 0 && (map->monitoring == 6)) //ignorar linha vazia
		{
			free(*line);
			continue;
		}
		else
		{
			map->monitoring = 0;
			map->map[content] = *line;
			content++;
		}
		// if(*line)
			// free(*line);
	}
	printf("Textura: %s\n", map->textures.west_wall);
	*line = NULL;
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
			file_error(); //monitoring_content();
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
			{
				monitoring += 2;//significa que passou pelo rgb
				free(*line);
				continue;
			}
		}
		if(ft_strlen(*line) == 0 && map->height == 0)//se nao é linha vazia e nao é 2
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
	// if(line && *line)
	// {
	// 	free(*line);
	// 	*line = NULL;
	// }
	if (map->height == 0)
	{
		close(map->fd);
		file_error();
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
		exit(-1);
	}
	measure_height(&line, map);
	store_map(&line, map, filename);
	// int i = 0;
	// int j = 0;
	// while (map->map[i])
	// {
	// 	j = 0;
	// 	while(map->map[i][j]) {
	// 		printf("%c", map->map[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	close(map->fd);
	return (map);
}

/*
./cub3d ./src/maps/map.cub
./cub3d ./src/maps/map3.cub
*/