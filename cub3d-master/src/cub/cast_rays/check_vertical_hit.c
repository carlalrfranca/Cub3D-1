/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:42:18 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/09 08:38:38 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_vertical_hit(t_map *map, float *vx, float *vy)
{
	init_ray_projection_values(map, vx, vy, &map->rays.dist_vertical);
	map->rays.neg_tan = -tan(map->rays.ray_angle);
	if(map->rays.ray_angle > P2 || map->rays.ray_angle < P3) //olhando lado esquerdo //II e III quadrantes
	{
		// a gente tem que descobrir a distância do ponto do raio/jogador até a extremidade
		// da célula mais próxima na vertical (sideDistY) 
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) - 0.0001;
		map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
		map->rays.step_x = -map_s; //-32
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan; //neg_tan é uma razão pra multiplicar apenas? se for um angulo "pro alto", ele virá negativo, e pra baixo, positivo?
	}
	if(map->rays.ray_angle < P2 || map->rays.ray_angle > P3) //olhando lado direito //I e IV quadrantes
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
