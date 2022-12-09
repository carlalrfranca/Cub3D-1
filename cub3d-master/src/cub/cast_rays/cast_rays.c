/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:08:08 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/08 11:57:12 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int find_pixel_index(float *pixel_coord, int map_width)
{
    int pixel_x;
    int pixel_y;

    pixel_x = pixel_coord[0];
    pixel_y = pixel_coord[1];
    return (pixel_y * (map_width * map_s) + pixel_x);
}

int draw_ray_2d(t_ray *rays, t_background *map2d, int map_width, int color)
{
	float	delta_x;
	float	delta_y;
    float   pixel_coord[2];
    int     pixel_index;
	int     number_pixels;
	
	// coordenadas iniciais do raio a ser desenhado (posicao do pixel em x e y)
	pixel_coord[0] = rays->pos_x;
	pixel_coord[1] = rays->pos_y;
	delta_y = rays->ray_y - rays->pos_y; //endy - py; //0
	delta_x = rays->ray_x - rays->pos_x; //endx - px; //10
	number_pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
    //abaixo: calculo pra descobrir quantos pixels adicionar ao eixo x e ao eixo y
    //em cada iteração
    delta_x /= number_pixels; // 1
    delta_y /= number_pixels; // 0
    while (number_pixels)
    {
        pixel_index = find_pixel_index(pixel_coord, map_width);
    	map2d->data[pixel_index] = color;
    	pixel_coord[0] += delta_x;
    	pixel_coord[1] += delta_y;
    	--number_pixels;
    }
    return(0);
}

int check_smaller_ray(t_ray *rays, float *horiz_position, float *vert_position)
{
    int ray_color;
	// --------------- determine which ray is smaller so we cast it
	// if the vertical ray is smaller, we change the shade value
	if (rays->dist_vertical < rays->dist_horizontal)
	{
		rays->ray_x = vert_position[0];
		rays->ray_y = vert_position[1];
		rays->dist_final = rays->dist_vertical;
        ray_color = encode_rgb(54, 204, 207);
	}
	else if (rays->dist_horizontal < rays->dist_vertical)
	{
		rays->ray_x = horiz_position[0];
		rays->ray_y = horiz_position[1];
		rays->dist_final = rays->dist_horizontal;
        ray_color = encode_rgb(38, 153, 189);
	}
    return (ray_color);
}

void cast_rays(t_map *map)
{
	int     rays_counter; //r;
    float   horiz_position[2];
    float   vert_position[2];
    int     ray_color;

	map->rays.ray_angle = map->rays.gamer_angle - DR * 30; //angulo do raio
	keep_angle_limits(&map->rays.ray_angle);
	rays_counter = -1;
	while(++rays_counter < 160)
	{
		// -------------- linhas horizontais
		check_horizontal_hit(map, &horiz_position[0], &horiz_position[1]); 	//horiz_x horiz_y
		// -------------- linhas verticais
		check_vertical_hit(map, &vert_position[0], &vert_position[1]); //vert_x e vert_y
        ray_color = check_smaller_ray(&map->rays, horiz_position, vert_position);
        draw_ray_2d(&map->rays, &map->map2d, map->width, ray_color);
        // --------------- Desenhar paredes 3D -----------
		fix_fish_eye(&map->rays);
		draw_3d(&map->rays, map->rays.dist_final, rays_counter, map);
		// --------------- incrementa angulo para o próximo raio
		map->rays.ray_angle += DR/3;
		keep_angle_limits(&map->rays.ray_angle);
	}
	// coloca a imagem do fundo
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->back.ptr_img, 0, 0);
	// coloca o minimapa
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->map2d.ptr_img, 0, 0);
}
