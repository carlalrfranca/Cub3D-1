/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal_hit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:42:14 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/12 11:12:11 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static float	find_side_dist_x(t_ray *rays)
{
	float	inner_adjacent_side;

	inner_adjacent_side = (rays->pos_y - rays->ray_y) * rays->neg_inv_tan;
	return (rays->pos_x + inner_adjacent_side);
}

int	check_horizontal_hit(t_map *map, float *hx, float *hy)
{
	init_hit_data(map, hx, hy, &map->rays.dist_horizontal);
	map->rays.neg_inv_tan = -(1 / tan(map->rays.ray_angle));
	if (map->rays.ray_angle > PI)
	{
		map->rays.ray_y = (((int)map->rays.pos_y >> 5) << 5) - 0.0001;
		map->rays.ray_x = find_side_dist_x(&map->rays);
		map->rays.step_y = -MAP_S;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	else if (map->rays.ray_angle < PI)
	{
		map->rays.ray_y = (((int)map->rays.pos_y >> 5) << 5) + MAP_S;
		map->rays.ray_x = find_side_dist_x(&map->rays);
		map->rays.step_y = MAP_S;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	if (map->rays.ray_angle == 0 || map->rays.ray_angle == PI)
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->height;
	}
	find_hit(map, hx, hy, "horizontal");
	return (0);
}
