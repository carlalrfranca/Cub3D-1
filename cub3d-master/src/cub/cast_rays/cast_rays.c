/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:08:08 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/14 20:11:41 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_smaller_ray(t_ray *rays, float *horiz_coord, float *vert_coord)
{
	if (rays->dist_vertical < rays->dist_horizontal)
	{
		rays->ray_x = vert_coord[0];
		rays->ray_y = vert_coord[1];
		rays->dist_final = rays->dist_vertical;
	}
	else if (rays->dist_horizontal < rays->dist_vertical)
	{
		rays->ray_x = horiz_coord[0];
		rays->ray_y = horiz_coord[1];
		rays->dist_final = rays->dist_horizontal;
	}
	return (0);
}

void	cast_rays(t_map *map)
{
	int		rays_counter;
	float	horiz_coord[2];
	float	vert_coord[2];

	map->rays.ray_angle = map->rays.gamer_angle - DR * 30;
	keep_angle_limits(&map->rays.ray_angle);
	rays_counter = -1;
	while (++rays_counter < (SCREEN_WIDTH / 4))
	{
		check_horizontal_hit(map, &horiz_coord[0], &horiz_coord[1]);
		check_vertical_hit(map, &vert_coord[0], &vert_coord[1]);
		check_smaller_ray(&map->rays, horiz_coord, vert_coord);
		fix_fish_eye(&map->rays);
		draw_3d(&map->rays, map->rays.dist_final, rays_counter, map);
		map->rays.ray_angle += ((DR * 60) / (SCREEN_WIDTH / 4));
		keep_angle_limits(&map->rays.ray_angle);
	}
	mlx_put_image_to_window(map->mlx.mlx_ptr,
		map->mlx.win, map->back.ptr_img, 0, 0);
}
