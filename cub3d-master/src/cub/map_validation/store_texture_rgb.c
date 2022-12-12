/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_texture_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:28:34 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/12 11:34:13 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static void	save_texture(t_textures *textures, char *line, t_map *map)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		trimmed = ft_strdup(line);
	}
	if (ft_strncmp("NO ", trimmed, 3) == 0)
		textures->north_wall = ft_strtrim(ft_strchr(trimmed, ' '), " \t");
	else if (ft_strncmp("SO ", trimmed, 3) == 0)
		textures->south_wall = ft_strtrim(ft_strchr(trimmed, ' '), " \t");
	else if (ft_strncmp("WE ", trimmed, 3) == 0)
		textures->west_wall = ft_strtrim(ft_strchr(trimmed, ' '), " \t");
	else if (ft_strncmp("EA ", trimmed, 3) == 0)
		textures->east_wall = ft_strtrim(ft_strchr(trimmed, ' '), " \t");
	else
	{
		free(trimmed);
		invalid_texture(line, map, "Error\nWrong TEXTURE formatting");
	}
	free(trimmed);
}

static char	*save_rgb_code(char *line)
{
	char	*rgb_color;
	char	*trimmed;
	char	*rgb_trimmed;

	rgb_color = NULL;
	trimmed = ft_strtrim(line, " \t");
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		trimmed = ft_strdup(line);
	}
	rgb_color = ft_strchr(trimmed, ' ');
	if (!rgb_color)
		rgb_color = ft_strchr(trimmed, '\t');
	if (!rgb_color)
	{
		free(trimmed);
		return (NULL);
	}
	rgb_trimmed = ft_strtrim(rgb_color, " \t");
	free(trimmed);
	return (rgb_trimmed);
}

static void	check_which_rgb(char *line, char **floor, char **ceilling, t_map *map)
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

void	save_textures_rgb(char *line, t_map *map)
{
	if (is_texture_path(line))
		save_texture(&map->textures, line, map);
	else if (is_rgb_color(line))
		check_which_rgb(line, &map->floor, &map->ceilling, map);
}
