/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal_hit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:42:14 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 15:48:09 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_horizontal_hit(t_map *map, float *hx, float *hy)
{
	init_ray_projection_values(map, hx, hy, &map->rays.dist_horizontal);
	map->rays.neg_inv_tan = -1/tan(map->rays.ray_angle);
	if(map->rays.ray_angle > PI) //se tiver olhando para baixo
	{
		map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) - 0.0001;
		map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
		map->rays.step_y = -map_s;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	else if(map->rays.ray_angle < PI)//se tiver olhando pra cima
	{
		map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) + map_s;
		map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
		map->rays.step_y = map_s;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI)//olhando direto para esquerda ou direita
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->height; //antes era 8 (dof)
	}
    search_hit_point(map, hx, hy, "horizontal");
	return (0);
}