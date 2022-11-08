/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/07 21:48:09 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		if (ft_strncmp("NO ./", *line, 5) == 0)
			map->textures.north_wall = ft_strchr(*line, '.');		
		else if (ft_strncmp("SO ./", *line, 5) == 0)
			map->textures.south_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("WE ./", *line, 5) == 0)
			map->textures.west_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("EA ./", *line, 5) == 0)
			map->textures.east_wall = ft_strchr(*line, '.');	
		else if (ft_strncmp("F", *line, 1) == 0)
		{
			map->floor = ft_strchr(*line, ' ');
			to_trim = map->floor;
			map->floor = ft_strtrim(to_trim, " ");
		}
		else if (ft_strncmp("C", *line, 1) == 0)
		{
			map->ceilling = ft_strchr(*line, ' ');
			to_trim = map->ceilling;
			map->ceilling = ft_strtrim(to_trim, " ");	
		}
		else if(ft_strlen(*line) == 0 && (map->monitoring == 4 ||
			 map->monitoring == 2)) //ignorar linha vazia
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
	}
}

void	measure_height(char **line, t_map *map)
{
	int	size;
	int		ret;
	int		texture;
	int		rgb;
	int		monitoring;

	map->height = 0;
	map->width = 0;
	ret = 1;
	rgb = 0;
	texture = 0;
	monitoring = 0;
	//size = 0;
	while (ret)
	{
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0)
			file_error(); //monitoring_content();
		if (ft_strchr(*line, '.')) //texturas
		{
			texture++;
			if (texture == 4)
				monitoring = 4;
		}
		else if (ft_strchr(*line, ','))//floor e ceilling
		{
			rgb++;
			if(rgb == 2)
			{
				monitoring = 2;//significa que passou pelo rgb e que so restao mapa
				free(*line);
				continue;
			}
		}
		if(ft_strlen(*line) == 0 && map->height == 0)//se nao é linha vazia e nao é 2
		{
			free(*line);
			continue;
		}
		else if (monitoring == 2)
		{
			map->height++;
			size = ft_strlen(*line);
			if(size > map->width)
				map->width = size;
		}	
	}
	// printf("height: %d\n", map->height);
	if (map->height == 0)
	{
		close(map->fd);
		file_error();
	}//printf("***AQUI O TAMANHO DO HEIGHT %d\n", map->height);
	map->monitoring = monitoring;
	// printf("o tamanho da linha na width: %d\n", map->width);
}

t_map	*prepare_to_store(char *filename)
{
	t_map	*map;
	char	*line;

	line = 0;
	map = malloc(sizeof(t_map));
	//map->rays = malloc(sizeof(t_ray));
	map->fd = open(filename, O_RDONLY);
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
	// printf("Dimensões do mapa -> H: %d e W: %d\n", map->height, map->width);
	// printf("letra da ultima coluna linha 2: %c\n", map->map[2][34]);
	// printf("tamanho da linha 2: %ld\n", ft_strlen(map->map[2]));
	return (map);
}

/*
./cub3d ./src/maps/map.cub
*/