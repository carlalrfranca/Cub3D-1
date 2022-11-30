/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 18:18:59 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void fix_fish_eye(t_ray *rays)
{
	float gamer_to_ray_angle;

	gamer_to_ray_angle = rays->gamer_angle - rays->ray_angle;
	if(gamer_to_ray_angle < 0)
		gamer_to_ray_angle += 2*PI;
	else if (gamer_to_ray_angle > 2*PI)
		gamer_to_ray_angle -= 2*PI;
	rays->dist_final = rays->dist_final * cos(gamer_to_ray_angle);
}

void    draw_wall_strip(t_3dmap *map_3D, t_background *backg, t_ray *rays, int rays_counter)
{
	int     y;
    float   pixel_color;
    int     pixel_size;
    int     total_size;
    
    y = -1;
    while (++y < map_3D->line_height)
    {
    	pixel_color = (map_3D->data_tile)[(int)(map_3D->texture_y) * map_s + (int)(map_3D->texture_x)];
        // paredes no eixo y terão cor sombreada...
    	if (rays->dist_vertical < rays->dist_horizontal)
    	{
    		//para escurecer a cor um pouco: col = (col & 0xfefefe) >> 1;
    		pixel_color = ((int)pixel_color & 0xfefefe) >> 1;
    	}
    	pixel_size = rays_counter * 5;
    	total_size = pixel_size + 5;
    	while (pixel_size < total_size)
    	{
    		backg->data[(y + (int)map_3D->centered_vision) * SCREEN_WIDTH + (pixel_size)] = pixel_color;
    		pixel_size++;
    	}
    	map_3D->texture_y += map_3D->texture_y_step;
    }
}

static void    defines_wall_texture(t_3dmap *map_3D, t_ray *rays, t_image *textures)
{
    if(rays->dist_horizontal < rays->dist_vertical)
	{
		map_3D->texture_x = (int)(rays->ray_x/2.0) % map_s;
		if(rays->ray_angle > PI) //olhando para baixo
		{
			map_3D->data_tile = textures->south_tile.data;
			map_3D->texture_x = 31 - map_3D->texture_x;
		}
		else
			map_3D->data_tile = textures->north_tile.data;
	}
	else
	{
		map_3D->texture_x = (int)(rays->ray_y/2.0) % map_s;
		if (rays->ray_angle > P2 && rays->ray_angle < P3)
		{
			map_3D->data_tile = textures->west_tile.data;
			map_3D->texture_x = 31 - map_3D->texture_x;
		}
		else
			map_3D->data_tile = textures->east_tile.data;
	}
}

void draw_3d(t_ray *rays, float dist_final, int rays_counter, t_map *map)
{
    t_3dmap map_3D;

	// 1 - tirar a altura da coluna/tira de parede a ser desenhada
	map_3D.line_height = (map_s * SCREEN_HEIGHT/dist_final);
	map_3D.texture_y_step = 32.0/map_3D.line_height;
	// texture_y_off vai compensar o mapeamento da textura em y caso a altura
	// da parede estoure a altura da janela
	// pra que, na hora que estiver desenhando a textura
	// e chegar superar o tamanho de janela da projeção 3d, o
	// desenho não fique distorcido (perca a perspectiva)
	map_3D.texture_y_off = 0;
	if(map_3D.line_height > 800)
	{
		map_3D.texture_y_off = (map_3D.line_height - SCREEN_HEIGHT)/2.0;
		map_3D.line_height = SCREEN_HEIGHT - 1;
	}
	// precisamos centralizar a imagem (desenhar a tira da parede a partir de metade abaixo do total da altura da tela)
	map_3D.centered_vision = (SCREEN_HEIGHT/2) - (map_3D.line_height/2);
     // 'texture_y' calcula o valor 'y' das texturas
	map_3D.texture_y = map_3D.texture_y_off * map_3D.texture_y_step;
    // ------------- chooses the texture and set the texture_x
    defines_wall_texture(&map_3D, rays, &map->textures);
    draw_wall_strip(&map_3D, &map->back, &map->rays, rays_counter);
}
