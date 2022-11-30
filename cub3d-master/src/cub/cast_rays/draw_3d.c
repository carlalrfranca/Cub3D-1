/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 16:26:34 by cleticia         ###   ########.fr       */
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

void draw_3d(t_ray *ray, float dist_final, int rays_counter, t_map *map)
{	
	float	centered_vision;
	float	line_height;
	int	*data_tile;
    float   pixel_color;
	int     pixel_size;
	int     total_size;

    // variáveis usadas para mapear os pixels das texturas que estão sendo pintados
    float   texture_x;
    float   texture_y;
    float   texture_y_step;
    float   texture_y_off;
    
	// 2- tirar a altura da coluna/tira de parede a ser desenhada
	line_height = (map_s * 800/dist_final);
	texture_y_step = 32.0/line_height;
	// ty_off vai compensar o mapeamento da textura em y caso a altura
	// da parede estoure a altura da janela
	// pra que, na hora que estiver desenhando a textura
	// e chegar superar o tamanho de janela da projeção 3d, o
	// desenho não fique distorcido (perca a perspectiva)
	texture_y_off = 0;
	if(line_height > 800)
	{
		texture_y_off = (line_height - 800)/2.0;
		line_height = 800 - 1;
	}
	// precisamos centralizar a imagem (desenhar a tira da parede a partir de metade abaixo do total da altura da tela)
	centered_vision = 400 - line_height/2;
	int y;

    // 'texture_y' calcula o valor 'y' das texturas
	texture_y = texture_y_off * texture_y_step;
	if(map->rays.dist_horizontal < map->rays.dist_vertical)
	{
		texture_x = (int)(ray->ray_x/2.0) % map_s;
		if(ray->ray_angle > PI) //olhando para baixo
		{
			data_tile = map->textures.south_tile.data;
			texture_x = 31 - texture_x;
		}
		else
			data_tile = map->textures.north_tile.data;
	}
	else
	{
		texture_x = (int)(ray->ray_y/2.0) % map_s;
		if (ray->ray_angle > P2 && ray->ray_angle < P3)
		{
			data_tile = map->textures.west_tile.data;
			texture_x = 31 - texture_x;
		}
		else
			data_tile = map->textures.east_tile.data;
	}
    y = -1;
    while (++y < line_height)
    {
    	pixel_color = (data_tile)[(int)(texture_y) * map_s + (int)(texture_x)];
        // paredes no eixo y terão cor sombreada...
    	if (map->rays.dist_vertical < map->rays.dist_horizontal)
    	{
    		//para escurecer a cor um pouco: col = (col & 0xfefefe) >> 1;
    		pixel_color = ((int)pixel_color & 0xfefefe) >> 1;
    	}
    	// ---------------------
    	pixel_size = rays_counter * 5;
    	total_size = pixel_size + 5;
    	while (pixel_size < total_size)
    	{
    		map->back.data[(y + (int)centered_vision) * SCREEN_WIDTH + (pixel_size)] = pixel_color;
    		pixel_size++;
    	}
    	texture_y += texture_y_step;
    }
}
