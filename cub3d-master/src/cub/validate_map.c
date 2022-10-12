/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:36 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/11 17:17:03 by cleticia         ###   ########.fr       */
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
		// printf("%d ", rgb);
	}
	printf("\n");
	if(i != 3)
		file_error();
}

void	validate_texture(t_map *map)
{
	if(map->textures.north_wall == 0 || map->textures.south_wall == 0
		|| map->textures.west_wall == 0 || map->textures.east_wall == 0)
		map_error(map); //printf("%s\n", map->north_wall);
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
			// printf("%c", map->map[i][j]);
			letter = map->map[i][j];
			if (letter != '0' && letter != ' ' && letter != '1'
				&& letter != 'N' && letter != 'S' &&letter != 'E' && letter != 'W')
			{
				printf("erro na verif_char %c\n",letter);
				map_error(map);
			}
			if (letter == 'S' || letter == 'N' || letter == 'E'
				|| letter == 'W')
				map->spawing = letter;
			j++;
		}
		// printf("\n");
		i++;
	}
}

int	validate_map(t_map *map)
{
	//printf("floor: %s\n", map->floor);
	validate_rgb(map->floor);
	validate_rgb(map->ceilling);
	validate_texture(map);
	verif_char(map);
	return (0);
}
