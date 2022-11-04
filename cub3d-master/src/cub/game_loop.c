/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/04 01:34:11 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <stdint.h>
#include <sys/time.h>

int	end_program(t_map *map)
{
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->gamer.ptr_img);
	mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win);
	mlx_destroy_display(map->mlx.mlx_ptr);
	exit (0);
}

int	minimize_window(t_map *map)
{
 	mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->gamer.ptr_img);
	color_background(map);
	paint_map(map);	
	paint_gamer(map);
 	return (0);
}
/*
	float	deltax;//pdx; //delta x
	float 	deltay;//pdy; //delta y
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5; //pa gamer_angle;
	px, py posicao do jogador ta na estrutura pos_x, pos_y
*/
/*
draw_line(map->mlx.mlx_ptr, map->mlx.win, map->rays.pos_x, map->rays.pos_y, map->rays.ray_x, map->rays.ray_y, 0xFFCC00);
*/
int draw_line(t_map *map, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_pos_x;
	double	pixel_pos_y;
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

float dist (float ax, float ay, float bx, float by)
{

	return (sqrt((bx - ax) * (bx - ax) + (by -ay) * (by - ay)));

}

void draw_rays(t_map *map)
{
	int ct_rays; //r;
	
	int mx;
	int my;
	int mp;
	float hx;
	float hy;
	float vx;
	float vy;

	map->rays.ray_angle = map->rays.gamer_angle; //angulo do raio
	//map->rays.ray_angle = map->rays.gamer_angle - DR * 30;
	if (map->rays.ray_angle < 0)
		map->rays.ray_angle += 2 * PI;
	if (map->rays.ray_angle > 2 * PI)
		map->rays.ray_angle -= 2 * PI;
	ct_rays = -1;
	while(++ct_rays < 1)
	{//linhas horizontais
		map->rays.depth_of_field = 0;
		map->rays.dist_horizontal = 1000000;
		hx = map->rays.pos_x;
		hy = map->rays.pos_y;
		map->rays.neg_inv_tan = -1/tan(map->rays.ray_angle);
		if(map->rays.ray_angle > PI) //se tiver olhando para cima
		{
			map->rays.ray_y = (((int)map->rays.pos_y >> 5) << 5) -0.0001;
			map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
			map->rays.step_y = -32;
			map->rays.step_x =-map->rays.step_y * map->rays.neg_inv_tan;
		}
		else if(map->rays.ray_angle<PI)//se tiver olhando pra baixo
		{
			map->rays.ray_y = (((int)map->rays.pos_y >> 5) << 5) + 32;
			map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
			map->rays.step_y = 32;
			map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
		}
		if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI)//olhando direto para esquerda ou direita
		{
			map->rays.ray_x = map->rays.pos_x;
			map->rays.ray_y = map->rays.pos_y;
			map->rays.depth_of_field = 8;
		}
		while(map->rays.depth_of_field < 8)
		{
			mx = (int)map->rays.ray_x >> 5;
			my = (int)map->rays.ray_y >> 5;
			mp = my * map->rays.map_x + mx;
			if((mp > 0 && mp < (map->rays.map_x * map->rays.map_y)) && map->map[my][mx] == 1) //se bateu na parede entao para o loop
			{
				hx = map->rays.ray_x;
				hy = map->rays.ray_y;
				map->rays.dist_horizontal = dist(map->rays.pos_x, map->rays.pos_y, hx, hy);
				map->rays.depth_of_field = 8; // hit muro
			}
			else //se nao bateu incrementa o tamanho do raio
			{ //xo e yo é o comprimento interno da célula - do ponto inicial ao final
				map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
				map->rays.ray_y += map->rays.step_y;
				map->rays.depth_of_field += 1;
			}		
		}
		draw_line(map, 0xFFCC00);

		//linhas verticais
		map->rays.depth_of_field = 0; //triangulacao calculo de tirar inverso da tangente etc
		map->rays.dist_vertical = 1000000;
		vx = map->rays.pos_x;
		vy = map->rays.pos_y;
		map->rays.neg_tan =-tan(map->rays.ray_angle);
		if(map->rays.ray_angle > P2 || map->rays.ray_angle < P3) //olhando lado esquerdo
		{
			map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5)-0.0001;
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
			map->rays.depth_of_field = 8;
		}
		while(map->rays.depth_of_field < 8) // dof é a profundidade de campo
		{
			mx = (int)(map->rays.ray_x)>>5;
			my = (int)(map->rays.ray_y)>>5;
			mp = my * map->rays.map_x + mx;
			if(mp > 0 && mp < map->rays.map_x * map->rays.map_y && map->map[my][mx] == '1') //se bateu na parede entao para o loop
			{
				vx = map->rays.ray_x;
				vy = map->rays.ray_y;
				map->rays.dist_vertical = dist(map->rays.pos_x, map->rays.pos_y, vx, vy);
				map->rays.depth_of_field = 8; // hit muro
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
		if (map->rays.dist_horizontal < map->rays.dist_vertical)
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




void	paint_gamer(t_map *map)
{
	int pixel_horizontal;//x;
	int pixel_vertical;//y;

	map->gamer.ptr_img = mlx_new_image(map->mlx.mlx_ptr, 8, 8);
	map->gamer.data = (int *)mlx_get_data_addr(map->gamer.ptr_img, &map->gamer.bpp, &map->gamer.line_size, &map->gamer.endian);
	pixel_horizontal = 0;
	while (pixel_horizontal < 8)
	{
		pixel_vertical = 0;
		while (pixel_vertical < 8)
		{
			map->gamer.data[pixel_horizontal * 8 + pixel_vertical] = 0xFFCC00;
			pixel_vertical++;
		}
		pixel_horizontal++;
	}
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->gamer.ptr_img, map->rays.pos_x, map->rays.pos_y);
	//draw_line(mlx_ptr, win, px+4, py+4, px+pdx*5, py+pdy*5, 0xFF6347);
	draw_rays(map);
}

void	paint_map(t_map *map)
{
	int cell_horizontal;//x;
	int cell_vertical;//y;
	int px_begin_horizontal;//xo;//pixel inicial da celula em horizontal
	int px_begin_vertical;//yo;// pixel inicial da celula em vertical

	//estabelece o tam do quadrado dentro da tela, por cima do backgrground
	map->map2d.ptr_img = mlx_new_image(map->mlx.mlx_ptr, map->width * 32, map->height * 32);
	map->map2d.data = (int *)mlx_get_data_addr(map->map2d.ptr_img, &map->map2d.bpp, &map->map2d.line_size, &map->map2d.endian);
	cell_horizontal = 0;
	while (cell_horizontal < map->width)
	{
		cell_vertical = 0;
		while (cell_vertical < map->height)
		{
			px_begin_horizontal = cell_horizontal * map_s; 
			while (px_begin_horizontal < (map_s * (cell_horizontal + 1)))
			{
				px_begin_vertical = cell_vertical * map_s;
				while (px_begin_vertical < (map_s * (cell_vertical + 1)))
				{
					//printf("cell_h: %d e cell_v: %d\n", cell_horizontal, cell_vertical);
					if(map->map[cell_vertical][cell_horizontal] == '1')
						map->map2d.data[px_begin_vertical * (map->width * 32) + px_begin_horizontal] = 0x000000;
					else
						map->map2d.data[px_begin_vertical * (map->width * 32) + px_begin_horizontal] = 0xFFFFFF;
					px_begin_vertical++;
				}
				px_begin_horizontal++;
			}
			cell_vertical++;
		}
		cell_horizontal++;
	}
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->map2d.ptr_img, 5, 5);
}

void	color_background(t_map *map) //pintar a tela
{  
    int columns = -1;
    int rows;

	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img, &map->back.bpp, &map->back.line_size, &map->back.endian);
    while (++columns < SCREEN_HEIGHT)
    {
        rows = -1;
        while (++rows < SCREEN_WIDTH)
			map->back.data[columns * SCREEN_WIDTH + rows] = 0x5C5C5C;;
    }
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->back.ptr_img, 0, 0);
}


int	event_key(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}	
	if (keycode == KEY_A)
	{
		map->rays.gamer_angle -= 0.1;
		if (map->rays.gamer_angle < 0)
			map->rays.gamer_angle += 2* PI;
		map->rays.deltax = cos(map->rays.gamer_angle) * 5;
		map->rays.deltay = sin(map->rays.gamer_angle) * 5;
	}
	if (keycode == KEY_D)
	{ 
		map->rays.gamer_angle += 0.1;
		if (map->rays.gamer_angle > 2 * PI)
			map->rays.gamer_angle -= 2* PI;
		map->rays.deltax = cos(map->rays.gamer_angle) * 5;
		map->rays.deltay = sin(map->rays.gamer_angle) * 5;
 	} 
 	if (keycode == KEY_W)
 	{ 
		map->rays.pos_x += map->rays.deltax; 
		map->rays.pos_y += map->rays.deltay;
		if (map->rays.pos_x < 0)
			map->rays.pos_x = 1;
		if (map->rays.pos_y < 0)
			map->rays.pos_y = 1;
 	}
 	if (keycode == KEY_S)
 	{ 
		map->rays.pos_x -= map->rays.deltax; 
		map->rays.pos_y -= map->rays.deltay;
		if (map->rays.pos_x < 0)
			map->rays.pos_x = 1;
		if (map->rays.pos_y < 0)
			map->rays.pos_y = 1;
 	}
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->gamer.ptr_img);
	color_background(map);
	paint_map(map);
	paint_gamer(map);
	return 0;
}

void	game_loop(t_map *map)
{
	// int	x;
	// int	y;
	// x = map->width * 32;
	// y = map->height * 32;
	map->rays.pos_x = 10;
	map->rays.pos_y = 10;
	printf("coordenadas player: %f e %f\n", map->rays.pos_x, map->rays.pos_y);
	map->rays.deltax = cos(map->rays.gamer_angle) * 5;
	map->rays.deltay = sin(map->rays.gamer_angle) * 5;
	map->mlx.mlx_ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	color_background(map);
	paint_map(map);	
	paint_gamer(map);
	mlx_hook(map->mlx.win, X_EVENT_KEY_PRESS, 1L << 0, event_key, map);
	mlx_hook(map->mlx.win, X_EVENT_KEY_EXIT, 1L << 0, end_program, map);
	mlx_expose_hook(map->mlx.win, minimize_window, map);
	mlx_loop(map->mlx.mlx_ptr);
}

/*
./cub3d ./src/maps/map.cub
*/
