/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:42:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/12 11:17:11 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static float	find_side_dist_y(t_ray *rays)
{
	float	inner_adjacent_side;

	inner_adjacent_side = (rays->pos_x - rays->ray_x) * rays->neg_tan;
	return (rays->pos_y + inner_adjacent_side);
}

/*
	-> (map->rays.ray_angle > P2 || map->rays.ray_angle < P3)
		é igual a -> olhando lado esquerdo //II e III quadrantes
	Os calculos dentro dos ifs sao:
	a gente tem que descobrir a distância do ponto do raio/jogador
	até a extremidade da célula mais próxima na vertical (sideDistY) 

	->  neg_tan é uma razão pra multiplicar apenas? se for
	um angulo "pro alto", ele virá negativo, e pra baixo, positivo?
*/
int	check_vertical_hit(t_map *map, float *vx, float *vy)
{
	init_hit_data(map, vx, vy, &map->rays.dist_vertical);
	map->rays.neg_tan = -tan(map->rays.ray_angle);
	if (map->rays.ray_angle > P2 || map->rays.ray_angle < P3)
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) - 0.0001;
		map->rays.ray_y = find_side_dist_y(&map->rays);
		map->rays.step_x = -MAP_S;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}
	if (map->rays.ray_angle < P2 || map->rays.ray_angle > P3)
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) + MAP_S;
		map->rays.ray_y = find_side_dist_y(&map->rays);
		map->rays.step_x = MAP_S;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}
	if (map->rays.ray_angle == 0 || map->rays.ray_angle == PI)
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->width;
	}
	find_hit(map, vx, vy, "vertical");
	return (0);
}
