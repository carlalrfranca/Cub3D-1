/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:42:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 13:34:09 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_vertical_hit(t_map *map, float *vx, float *vy)
{
	init_ray_projection_values(map, vx, vy, &map->rays.dist_vertical);
	map->rays.neg_tan = -tan(map->rays.ray_angle);
	if(map->rays.ray_angle > P2 || map->rays.ray_angle < P3) //olhando lado esquerdo
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) - 0.0001;
		map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
		map->rays.step_x = -map_s;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}
	if(map->rays.ray_angle < P2 || map->rays.ray_angle > P3) //olhando lado direito
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) + map_s;
		map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
		map->rays.step_x = map_s;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}		
	if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI) //olhando para cima ou para baixo
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->width; // antes 8 (dof)
	}
    search_hit_point(map, vx, vy, "vertical");
	return (0);
}
