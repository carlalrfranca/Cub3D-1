/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:08:08 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/12 20:51:56 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int draw_line(t_map *map, int color)
{
	float	delta_x;
	float	delta_y;
	float	pixel_pos_x;
	float	pixel_pos_y;
	int		numberPixels;
	
	// coordenadas iniciais do raio a ser desenhado (posicao do pixel em x e y)
	pixel_pos_x = map->rays.pos_x;
	pixel_pos_y = map->rays.pos_y;

	delta_y = map->rays.ray_y - map->rays.pos_y; //endy - py; //0
	delta_x = map->rays.ray_x - map->rays.pos_x; //endx - px; //10
	numberPixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));

	//abaixo: calculo pra descobrir quantos pixels adicionar ao eixo x e ao eixo y
	//em cada iteração
	delta_x /= numberPixels; // 1
	delta_y /= numberPixels; // 0
	while (numberPixels)
	{
    	mlx_pixel_put(map->mlx.mlx_ptr, map->mlx.win, pixel_pos_x, pixel_pos_y, color);
    	pixel_pos_x += delta_x;
    	pixel_pos_y += delta_y;
    	--numberPixels;
	}
	return(0);
}

float measure_ray_dist(float beginX, float beginY, float endX, float endY)
{
	float catetoX_squared;
	float catetoY_squared;

	catetoX_squared = (endX - beginX) * (endX - beginX);
	catetoY_squared = (endY - beginY) * (endY - beginY);
	return (sqrt(catetoX_squared + catetoY_squared));
}

// void	check_horizontal_hit(t_map *map, float hx, float hy)
// {

// }

// void	check_vertical_hit(t_map *map, float vx, float vy)
// {
	
// }

void draw_rays(t_map *map)
{
	int ct_rays; //r;
	
	int mx;
	int my;
	// int mp;
	float hx;
	float hy;
	float vx;
	float vy;

	// printf("Profundidade de campo na horizontal: %d e vertical: %d\n", map->width, map->height);
	map->rays.ray_angle = map->rays.gamer_angle - DR * 10; //angulo do raio
	// map->rays.ray_angle = map->rays.gamer_angle - DR * 30;
	if (map->rays.ray_angle < 0)
		map->rays.ray_angle += 2*PI;
	if (map->rays.ray_angle > 2*PI)
		map->rays.ray_angle -= 2*PI;
	ct_rays = -1;
	while(++ct_rays < 30)
	{//linhas horizontais
		map->rays.depth_of_field = 0;
		map->rays.dist_horizontal = 1000000;
		hx = map->rays.pos_x;
		hy = map->rays.pos_y;
		map->rays.neg_inv_tan = -1/tan(map->rays.ray_angle);
		if(map->rays.ray_angle > PI) //se tiver olhando para cima
		{
			map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) - 0.0001;
			map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
			map->rays.step_y = -32;
			map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
		}
		else if(map->rays.ray_angle < PI)//se tiver olhando pra baixo
		{
			map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) + 32;
			map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
			map->rays.step_y = 32;
			map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
		}
		if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI)//olhando direto para esquerda ou direita
		{
			map->rays.ray_x = map->rays.pos_x;
			map->rays.ray_y = map->rays.pos_y;
			map->rays.depth_of_field = map->height; //antes era 8 (dof)
		}
		while(map->rays.depth_of_field < map->height) //antes era < 8 (dof)
		{
			mx = (int)map->rays.ray_x >> 5;
			my = (int)map->rays.ray_y >> 5;
			// mp = my * map->rays.map_x + mx;
			if((mx >= 0 && mx < map->width) && (my >= 0 && my < map->height) && map->map[my][mx] == '1') //se bateu na parede entao para o loop //mp > 0 && mp < (map->rays.map_x * map->rays.map_y) && 
			{
				hx = map->rays.ray_x;
				hy = map->rays.ray_y;
				map->rays.dist_horizontal = measure_ray_dist(map->rays.pos_x, map->rays.pos_y, hx, hy);
				map->rays.depth_of_field = map->height; // hit muro (maxima de celulas de altura no mapa -> no modelo é 8 por 8)
			}
			else //se nao bateu incrementa o tamanho do raio
			{ //xo e yo é o comprimento interno da célula - do ponto inicial ao final
				map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
				map->rays.ray_y += map->rays.step_y;
				map->rays.depth_of_field += 1;
			}		
		}
		// draw_line(map, 0xFFCC00);

		//linhas verticais
		map->rays.depth_of_field = 0; //triangulacao calculo de tirar inverso da tangente etc
		map->rays.dist_vertical = 1000000;
		vx = map->rays.pos_x;
		vy = map->rays.pos_y;
		map->rays.neg_tan = -tan(map->rays.ray_angle);
		if(map->rays.ray_angle > P2 || map->rays.ray_angle > P3) //olhando lado esquerdo
		{
			map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) - 0.0001;
			map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
			map->rays.step_x = -32;
			map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
		}

		if(map->rays.ray_angle < P2 || map->rays.ray_angle > P3) //olhando lado direito
		{
			map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) + 32;
			map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
			map->rays.step_x = 32;
			map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
		}		
		
		if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI) //olhando para cima ou para baixo
		{
			map->rays.ray_x = map->rays.pos_x;
			map->rays.ray_y = map->rays.pos_y;
			map->rays.depth_of_field = map->width; // antes 8 (dof)
		}
		while(map->rays.depth_of_field < map->width) // dof é a profundidade de campo (antes 8 como no modelo do mapa 8 por 8)
		{
			mx = (int)(map->rays.ray_x)>>5;
			my = (int)(map->rays.ray_y)>>5;
			// mp = my * map->rays.map_x + mx;
			if((mx >= 0 && mx < map->width) && (my >= 0 && my < map->height) && map->map[my][mx] == '1') //se bateu na parede entao para o loop //mp > 0 && mp < (map->rays.map_x * map->rays.map_y) &&
			{
				vx = map->rays.ray_x;
				vy = map->rays.ray_y;
				map->rays.dist_vertical = measure_ray_dist(map->rays.pos_x, map->rays.pos_y, vx, vy);
				map->rays.depth_of_field = map->width; // hit muro (antes 8 de acordo com o mapa 8x8)
			}
			else //se nao bateu incrementa o tamanho do raio
			{ //xo e yo é o comprimento interno da célula - do ponto inicial ao final
				map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
				map->rays.ray_y += map->rays.step_y; //hit muro
				map->rays.depth_of_field += 1; //próxima linha
			}			
		}
		if (map->rays.dist_vertical < map->rays.dist_horizontal)
		{
			map->rays.ray_x = vx;
			map->rays.ray_y = vy;
		}
		else if (map->rays.dist_horizontal < map->rays.dist_vertical)
		{
			map->rays.ray_x = hx;
			map->rays.ray_y = hy;
		}
		draw_line(map, 0xFFCC00);
		map->rays.ray_angle += DR;
		if (map->rays.ray_angle < 0)
			map->rays.ray_angle += 2 * PI;
		if (map->rays.ray_angle > 2 * PI)
			map->rays.ray_angle -= 2 * PI;
	}
}
