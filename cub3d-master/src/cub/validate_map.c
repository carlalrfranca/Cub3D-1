/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:36 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/08 00:26:38 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_map *map)
{
	int	index;

	index = -1;
	while (++index < map->height)
		free(map->map[index]);
	free(map->map);
}

void	map_error(t_map *map)
{
	free_map(map);
	write(2, "Error : Invalid Map\n", 20);
	exit(1);
}

int	is_two_commas(char *rgb_value)
{
	int	index;
	int	total_commas;

	index = 0;
	total_commas = 0;
	while (rgb_value[index])
	{
		if (rgb_value[index] == ',')
			total_commas++;
		index++;
	}
	if (total_commas != 2)
		return (0);
	return (1);
}

void	validate_rgb(char *rgb_value)
{
	char **split_values;
	int	rgb;
	int	i;
	int	j;

	i = -1;
	rgb = 0;
	if (!is_two_commas(rgb_value))
		file_error();
	split_values = ft_split(rgb_value, ',');
	while(split_values[++i])
	{
		j = -1;
		while (split_values[i][++j])
		{
			if(ft_isdigit(split_values[i][j]) == -1)
				file_error();
		}
		rgb = ft_atoi(split_values[i]);		
		if (rgb < 0 || rgb > 255)
			file_error();
	}
	if(i != 3)
		file_error();
}

void	validate_texture(t_map *map)
{
	if(map->textures.north_wall == 0 || map->textures.south_wall == 0
		|| map->textures.west_wall == 0 || map->textures.east_wall == 0)
		map_error(map);
}

void verif_char(t_map *map)
{
	char	letter;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			letter = map->map[i][j];
			if (letter != '0' && letter != ' ' && letter != '1'
				&& letter != 'N' && letter != 'S' &&letter != 'E' && letter != 'W')
			{
				map_error(map);
			}
			if (letter == 'S' || letter == 'N' || letter == 'E'
				|| letter == 'W')
			{
				map->spawing = letter;
				map->rays.pos_x = j;
				map->rays.pos_y = i;
			}
			j++;
		}
		i++;
	}
}

int validate_row(char **map, int pos_x, int pos_y, char to_skip)
{
	int x;

	x = pos_x;
	if (x > 0 && map[pos_y][x - 1] != '1')
		return (-30);
	while (map[pos_y][x] && map[pos_y][x] == to_skip)
		x++;
	if (map[pos_y][pos_x] == ' ' && map[pos_y][x] == '\0' && map[pos_y][pos_x - 1] == '1')
	{
		return (x - 1); //nesse caso, é o caracter nulo e vai precisar compensar pra la fora
		// nao acessarmos espaço indevido na string
	}
	else if (map[pos_y][x] != '1')
	{
		printf("%d e %d\n", pos_y, x); //ta dando erro pq ta pegando o caracter do gamer.. podemos
		// salvar sua posicao em x e y e substitui-lo por 0 pra nao ter problema?
		return (-30);
	}
	else
		return (x);
}

int is_map_open(t_map *map)
{
	int x_axis;
	int y_axis;
	int	skip_spaces;

	y_axis = 0;
	while(map->map[y_axis])
	{
		x_axis = 0;
		while (map->map[y_axis][x_axis])
		{
			if(map->map[y_axis][x_axis] == ' ')
			{
				// rodar até encontrar '1' (e atualizar a pos_x), senao dá erro
				skip_spaces = validate_row(map->map, x_axis, y_axis, ' ');
				if (skip_spaces < 0)
					return (skip_spaces);
				else
					x_axis += (skip_spaces - x_axis); //atualizar a posicao em x
			}
			else if (map->map[y_axis][x_axis] == '0')
			{
				// printf("Encontrou zero: %d e %d\n", y_axis, x_axis);
				skip_spaces = validate_row(map->map, x_axis, y_axis, '0');
				if (skip_spaces < 0)
					return (skip_spaces);
				else
					x_axis += (skip_spaces - x_axis);
			}
			x_axis++;
		}
		y_axis++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	validate_rgb(map->floor);
	validate_rgb(map->ceilling);
	validate_texture(map);
	verif_char(map);
	if (is_map_open(map) < 0)
	{
		printf("Erro\nSeu mapa não está fechado!");
		exit(-30);
	}
	return (0);
}
/*
./cub3d ./src/maps/map.cub
*/