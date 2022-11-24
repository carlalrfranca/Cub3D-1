/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/24 13:54:32 by cleticia         ###   ########.fr       */
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
	// variables to check colision...
	int offset_x;
	int offset_y;
	int collision_pos_x;
	int collision_pos_y;
	int	col_pos_x_add_offset_x;
	int	col_pos_y_add_offset_y;
	int col_pos_y_sub_offset_y;
	int col_pos_x_sub_offset_x;

	offset_x = 0;
	offset_y = 0;
	if (map->rays.deltax < 0)
		offset_x =-20;
	else
		offset_x = 20;
	if (map->rays.deltay < 0)
		offset_y = -20;
	else
		offset_y = 20;
	
	collision_pos_x = map->rays.pos_x/32.0;
	collision_pos_y = map->rays.pos_y/32.0;
	col_pos_x_add_offset_x = (map->rays.pos_x + offset_x)/32.0;
	col_pos_y_add_offset_y = (map->rays.pos_y + offset_y)/32.0;
	col_pos_y_sub_offset_y = (map->rays.pos_y - offset_y)/32.0;
	col_pos_x_sub_offset_x = (map->rays.pos_x - offset_x)/32.0;

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
		// esse primeiro if faz com que ele "deslize" no eixo x quando contra uma parede
		// garantindo tambem um "offset" no eixo x, ou seja, se houver '1' no offset de x
		// (lateral do gamer) ele não avança mais, só enquanto for '0'..
		if (map->map[collision_pos_y][col_pos_x_add_offset_x] == '0')
		{
			map->rays.pos_x += map->rays.deltax;
		}
		if (map->map[col_pos_y_add_offset_y][collision_pos_x] == '0')
		{
			map->rays.pos_y += map->rays.deltay;
		}
		// if(map->map[(int)map->rays.pos_y>>5][(int)map->rays.pos_x>>5] != '1')
		// map->rays.pos_x += map->rays.deltax;
		// map->rays.pos_y += map->rays.deltay;
		// printf("Posicao x e y: %f, %f\n----\n", map->rays.pos_x, map->rays.pos_y);
		// printf("Pro mapa --> x: %d, y: %d\n----\n", (int)map->rays.pos_x>>5, (int)map->rays.pos_y>>5);
		if (map->rays.pos_x < 0)
			map->rays.pos_x = 1;
		if (map->rays.pos_y < 0)
			map->rays.pos_y = 1;
 	}
 	if (keycode == KEY_S)
 	{
		// poder "recuar" no eixo x.. se houver '1', ele nao recua
		if (map->map[collision_pos_y][col_pos_x_sub_offset_x] == '0')
		{
			map->rays.pos_x -= map->rays.deltax;	
		}
		if (map->map[col_pos_y_sub_offset_y][collision_pos_x] == '0')
		{
			map->rays.pos_y -= map->rays.deltay;
		}
		if (map->rays.pos_x < 0)
			map->rays.pos_x = 1;
		if (map->rays.pos_y < 0)
			map->rays.pos_y = 1;
 	}
	// mlx_destroy_image (map->mlx.mlx_ptr, map->gamer.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	color_background(map);
	// mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->map2d.ptr_img, 0, 0);
	paint_map(map);
	paint_gamer(map);
	return 0;
}


static int	check_resolution(t_map *map)
{
	int	resolutionX;
	int	resolutionY;

	mlx_get_screen_size(map->mlx.mlx_ptr, &resolutionX, &resolutionY);
	if ((map->height * 32) >= resolutionY || (map->width * 32) >= resolutionX)
	{
		mlx_destroy_display(map->mlx.mlx_ptr);
		ft_putendl_fd("Your map overflowed the resolution!", 2);
		map_error(map);
	}
	return (0);
}

static void init_gamer_angle(char spawning, float *gamer_angle)
{
	if(spawning == 'N')
		*gamer_angle = P3;
	else if (spawning == 'S')
		*gamer_angle = P2;
	else if (spawning == 'E')
		*gamer_angle = 0;
	else
		*gamer_angle = PI;
	return; 
}

void	textures_init(t_image *textures, t_mlx *mlx)
{
	textures->west_tile.ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr,textures->west_wall, &textures->width, &textures->height);
	textures->west_tile.data = (int *)mlx_get_data_addr(textures->west_tile.ptr_img, &textures->west_tile.bpp, &textures->west_tile.line_size, &textures->west_tile.endian);

	textures->east_tile.ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr,textures->east_wall, &textures->width, &textures->height);
	textures->east_tile.data = (int *)mlx_get_data_addr(textures->east_tile.ptr_img, &textures->east_tile.bpp, &textures->east_tile.line_size, &textures->east_tile.endian);

	textures->north_tile.ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr,textures->north_wall, &textures->width, &textures->height);
	textures->north_tile.data = (int *)mlx_get_data_addr(textures->north_tile.ptr_img, &textures->north_tile.bpp, &textures->north_tile.line_size, &textures->north_tile.endian);

	textures->south_tile.ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr,textures->south_wall, &textures->width, &textures->height);
	textures->south_tile.data = (int *)mlx_get_data_addr(textures->south_tile.ptr_img, &textures->south_tile.bpp, &textures->south_tile.line_size, &textures->south_tile.endian);
}

void	rays_struct_init(t_map *map)
{
	// map->rays.pos_x = 40;
	// map->rays.pos_y = 80;
	textures_init(&map->textures, &map->mlx);
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
	map->mlx.mlx_ptr = mlx_init();
	check_resolution(map);
	rays_struct_init(map);
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	color_background(map);
	init_gamer_angle(map->spawing, &map->rays.gamer_angle);
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
