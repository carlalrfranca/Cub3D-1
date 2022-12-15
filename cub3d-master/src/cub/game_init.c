/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:47:01 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/14 20:57:26 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_resolution(t_map *map)
{
	int	resolution_x;
	int	resolution_y;

	mlx_get_screen_size(map->mlx.mlx_ptr, &resolution_x, &resolution_y);
	if (SCREEN_HEIGHT >= resolution_y || SCREEN_WIDTH >= resolution_x)
	{
		mlx_destroy_display(map->mlx.mlx_ptr);
		free(map->mlx.mlx_ptr);
		ft_putendl_fd("Your map overflowed the resolution!", 2);
		map_error(map);
	}
	return (0);
}

void	init_gamer_angle(char spawning, float *gamer_angle)
{
	if (spawning == 'N')
		*gamer_angle = (3 * PI / 2);
	else if (spawning == 'S')
		*gamer_angle = (PI / 2);
	else if (spawning == 'E')
		*gamer_angle = 0;
	else
		*gamer_angle = PI;
	return ;
}

int	open_texture(t_mlx *mlx, t_image *tile, int *coord, char *path)
{
	tile->ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&coord[0], &coord[1]);
	if (!tile->ptr_img)
		return (404);
	tile->data = (int *)mlx_get_data_addr(tile->ptr_img,
			&tile->bpp, &tile->line_size, &tile->endian);
	return (0);
}

int	textures_init(t_textures *textures, t_mlx *mlx)
{
	char	*path;
	int		coord[2];

	coord[0] = textures->width;
	coord[1] = textures->height;
	path = textures->west_wall;
	if (open_texture(mlx, &textures->west_tile, coord, path) == 404)
		return (404);
	path = textures->east_wall;
	if (open_texture(mlx, &textures->east_tile, coord, path) == 404)
		return (404);
	path = textures->north_wall;
	if (open_texture(mlx, &textures->north_tile, coord, path) == 404)
		return (404);
	path = textures->south_wall;
	if (open_texture(mlx, &textures->south_tile, coord, path) == 404)
		return (404);
	return (0);
}

int	rays_struct_init(t_map *map)
{
	map->back.ptr_img = NULL;
	map->mlx.win = NULL;
	map->textures.east_tile.ptr_img = NULL;
	map->textures.west_tile.ptr_img = NULL;
	map->textures.north_tile.ptr_img = NULL;
	map->textures.south_tile.ptr_img = NULL;
	if (textures_init(&map->textures, &map->mlx) == 404)
		return (404);
	map->rays.map_x = map->width;
	map->rays.map_y = map->height;
	init_gamer_angle(map->spawing, &map->rays.gamer_angle);
	map->rays.deltax = cos(map->rays.gamer_angle) * 5;
	map->rays.deltay = sin(map->rays.gamer_angle) * 5;
	return (0);
}
