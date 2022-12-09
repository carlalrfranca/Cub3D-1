/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_minimize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:06:54 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/09 18:33:46 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static void	destroy_images(t_map *map)
{
	if (map->back.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
	if (map->map2d.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->map2d.ptr_img);
	if (map->textures.east_tile.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->textures.east_tile.ptr_img);
	if (map->textures.west_tile.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->textures.west_tile.ptr_img);
	if (map->textures.north_tile.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->textures.north_tile.ptr_img);
	if (map->textures.south_tile.ptr_img)
		mlx_destroy_image(map->mlx.mlx_ptr, map->textures.south_tile.ptr_img);
	if (map->mlx.win)
		mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win);
	mlx_destroy_display(map->mlx.mlx_ptr);
}

int	end_program(t_map *map)
{
	destroy_images(map);
	free(map->mlx.mlx_ptr);
	free_matrix(map->map);
	free(map->map);
	map->map = NULL;
	if (ft_strlen(map->textures.east_wall) > 0)
		free(map->textures.east_wall);
	if (ft_strlen(map->textures.west_wall) > 0)
		free(map->textures.west_wall);
	if (ft_strlen(map->textures.north_wall) > 0)
		free(map->textures.north_wall);
	if (ft_strlen(map->textures.south_wall) > 0)
		free(map->textures.south_wall);
	if (map->ceilling)
		free(map->ceilling);
	if (map->floor)
		free(map->floor);
	free(map);
	exit (0);
}

int	minimize_window(t_map *map)
{
	mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->map2d.ptr_img);
	color_background(map);
	paint_map(map);
	paint_gamer(map);
	return (0);
}
