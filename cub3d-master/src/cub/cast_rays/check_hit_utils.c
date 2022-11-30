/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:45:12 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 13:58:03 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void init_ray_projection_values(t_map *map, float *rayX, float *rayY, float *ray_dist)
{
	map->rays.depth_of_field = 0;
	*ray_dist = 1000000;
	*rayX = map->rays.pos_x;
	*rayY = map->rays.pos_y;
}

float measure_ray_dist(float beginX, float beginY, float endX, float endY)
{
	float cateto_x_squared;
	float cateto_y_squared;

	cateto_x_squared = (endX - beginX) * (endX - beginX);
	cateto_y_squared = (endY - beginY) * (endY - beginY);
	return (sqrt(cateto_x_squared + cateto_y_squared));
}


int is_wall_hit(t_ray *rays, int map_width, int map_height, char **map)
{
    int map_x;
	int map_y;

    map_x = (int)rays->ray_x >> 5; //ray_x e ray_y é a posicao x e y ATUAL
	map_y = (int)rays->ray_y >> 5; //do raio (current_ray_x e current_ray_y)
    if(((map_x >= 0 && map_x < map_width) && (map_y >= 0
        && map_y < map_height)) && map[map_y][map_x] == '1')
            return (1);
    return (0);
}

void    check_axis(int *axis_depth, t_map *map, float **ray_axis, char *axis)
{
    if(ft_strncmp(axis, "horizontal", ft_strlen(axis)) == 0)
    {
        (*axis_depth) = map->height;
        (*ray_axis) = &map->rays.dist_horizontal;
    }
    else
    {
        (*axis_depth) = map->width;
        (*ray_axis) = &map->rays.dist_vertical;
    }
}

void    search_hit_point(t_map *map, float *ray_end_x, float *ray_end_y, char *axis)
{
    //abaixo: definidos de acordo com a string axis
    int axis_depth; //height pra horizontal, width pra vertical
    float *final_dist_ray; //dist_horizontal p/ horizontal, dist_vertical pra vertical

    check_axis(&axis_depth, map, &final_dist_ray, axis);
	while(map->rays.depth_of_field < axis_depth)
	{
		if(is_wall_hit(&map->rays, map->width, map->height, map->map)) //se bateu na parede entao para o loop
		{
			*ray_end_x = map->rays.ray_x;
			*ray_end_y = map->rays.ray_y;
			(*final_dist_ray) = measure_ray_dist(map->rays.pos_x, map->rays.pos_y, *ray_end_x, *ray_end_y);
			map->rays.depth_of_field = axis_depth; // hit muro (maxima de celulas do mapa)
		}
		else //se nao bateu incrementa o tamanho do raio
		{ //step_x e step_y é o comprimento interno da célula - do ponto inicial ao final
			map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
			map->rays.ray_y += map->rays.step_y; 
			map->rays.depth_of_field += 1;
		}		
	}
}
