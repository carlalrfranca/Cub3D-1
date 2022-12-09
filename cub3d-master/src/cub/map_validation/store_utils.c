/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:26:32 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/08 20:09:41 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	free_textures(t_map *map)
{
	if (map->textures.east_wall)
		free(map->textures.east_wall);
	if (map->textures.west_wall)
		free(map->textures.west_wall);
	if (map->textures.north_wall)
		free(map->textures.north_wall);
	if (map->textures.south_wall)
		free(map->textures.south_wall);
}

void	invalid_texture(char *line, t_map *map)
{
	free_textures(map);
	if (map->map)
		free(map->map);
	free(map);
	write(2, "Error\nInvalid Map: TEXTURE Formating.\n", 38);
	free(line);
	exit(20);
}

void invalid_rgb(char *line, char *rgb_to_free, t_map *map)
{
	free_textures(map);
    if(map->map)
        free(map->map);
    free(map);
    write(2, "Error\nInvalid Map: RGB Formating.\n", 34);
    free(line);
	if(rgb_to_free)
	    free(rgb_to_free);
	exit(10);
}

int	is_texture_path(char *line)
{
	char *texture_trimmed;

	texture_trimmed = ft_strtrim(line, " \t");
	if (ft_strlen(texture_trimmed) == 0)
	{
		free(texture_trimmed);
		texture_trimmed = ft_strdup(line);
	}
	if (ft_strncmp("NO", texture_trimmed, 2) == 0
		|| ft_strncmp("SO", texture_trimmed, 2) == 0
			|| ft_strncmp("WE", texture_trimmed, 2) == 0
				|| ft_strncmp("EA", texture_trimmed, 2) == 0)
	{
			free(texture_trimmed);
			return (1);
	}
	free(texture_trimmed);
	return (0);
}

int is_rgb_color(char *line)
{
	char	*rgb_trimmed;

	rgb_trimmed = ft_strtrim(line, " \t");
	if (ft_strlen(rgb_trimmed) == 0)
	{
		free(rgb_trimmed);
		rgb_trimmed = ft_strdup(line);
	}
    if (ft_strncmp("F", rgb_trimmed, 1) == 0)
	{
		free(rgb_trimmed);
        return (1);
	}
    else if (ft_strncmp("C", rgb_trimmed, 1) == 0)
	{
		free(rgb_trimmed);
        return (2);
	}
	free(rgb_trimmed);
    return (0);
}
