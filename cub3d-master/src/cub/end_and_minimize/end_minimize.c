/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_minimize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:06:54 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/12 20:07:16 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	end_program(t_map *map)
{
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->gamer.ptr_img);
	mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win);
	mlx_destroy_display(map->mlx.mlx_ptr);
	exit (0);
}

int	minimize_window(t_map *map)
{
 	mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->gamer.ptr_img);
	color_background(map);
	paint_map(map);	
	paint_gamer(map);
 	return (0);
}
