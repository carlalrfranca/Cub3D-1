/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_texture_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:28:34 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/14 21:15:38 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static char	*extract_path(char *trim)
{
	char	*extracted_path;
	char	*trimmed_extracted_path;

	extracted_path = NULL;
	extracted_path = ft_strchr(trim, ' ');
	if (!extracted_path)
		extracted_path = ft_strchr(trim, '\t');
	trimmed_extracted_path = ft_strtrim(extracted_path, " \t");
	return (trimmed_extracted_path);
}

static void	save_texture(t_textures *textures, char *line, t_map *map)
{
	char	*trim;

	trim = ft_strtrim(line, " \t");
	if (ft_strlen(trim) == 0)
	{
		free(trim);
		trim = ft_strdup(line);
	}
	if ((!ft_strncmp("NO ", trim, 3)) || !ft_strncmp("NO\t", trim, 3))
		textures->north_wall = extract_path(trim);
	else if ((!ft_strncmp("SO ", trim, 3)) || !ft_strncmp("NO\t", trim, 3))
		textures->south_wall = extract_path(trim);
	else if ((!ft_strncmp("WE ", trim, 3)) || !ft_strncmp("NO\t", trim, 3))
		textures->west_wall = extract_path(trim);
	else if ((!ft_strncmp("EA ", trim, 3)) || !ft_strncmp("NO\t", trim, 3))
		textures->east_wall = extract_path(trim);
	else
	{
		free(trim);
		invalid_texture(line, map, "Error\nWrong TEXTURE formatting");
	}
	free(trim);
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

void	check_which_rgb(char *line, char **floor, char **ceilling, t_map *map)
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
