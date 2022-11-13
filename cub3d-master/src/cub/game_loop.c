/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/12 20:10:08 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	mlx_destroy_image (map->mlx.mlx_ptr, map->gamer.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	color_background(map);
	paint_map(map);
	paint_gamer(map);
	return 0;
}

void	rays_struct_init(t_map *map)
{
	map->rays.pos_x = 40;
	map->rays.pos_y = 80;
	map->rays.map_x = map->width;
	map->rays.map_y = map->height;
	map->rays.gamer_angle = PI;
	map->rays.deltax = cos(map->rays.gamer_angle) * 5;
	map->rays.deltay = sin(map->rays.gamer_angle) * 5;
}

void	game_loop(t_map *map)
{
	// int	x;
	// int	y;
	// x = map->width * 32;
	// y = map->height * 32;
	// printf("coordenadas player: %f e %f\n", map->rays.pos_x, map->rays.pos_y);
	// map_x e map_y é pra ser a largura e altura do mapa em celulas? (width e height, entao?)
	rays_struct_init(map);
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
