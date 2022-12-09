/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/08 11:57:07 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void    check_collision(t_ray *rays)
{
    // variables to check colision...
	int offset_x;
	int offset_y;

	offset_x = 0;
	offset_y = 0;
	if (rays->deltax < 0)
		offset_x =-20;
	else
		offset_x = 20;
	if (rays->deltay < 0)
		offset_y = -20;
	else
		offset_y = 20;
	rays->collision.col_pos_x = rays->pos_x/32.0;
	rays->collision.col_pos_y = rays->pos_y/32.0;
	rays->collision.col_pos_x_add_offset_x = (rays->pos_x + offset_x)/32.0;
	rays->collision.col_pos_y_add_offset_y = (rays->pos_y + offset_y)/32.0;
	rays->collision.col_pos_y_sub_offset_y = (rays->pos_y - offset_y)/32.0;
	rays->collision.col_pos_x_sub_offset_x = (rays->pos_x - offset_x)/32.0;
}

void    move_gamer(char **map, t_ray *rays, char *movement)
{
    if(!ft_strncmp(movement, "to_up", ft_strlen(movement)))
    {
        if(map[rays->collision.col_pos_y][rays->collision.col_pos_x_add_offset_x] == '0')
            rays->pos_x += rays->deltax;
        if(map[rays->collision.col_pos_y_add_offset_y][rays->collision.col_pos_x] == '0')
            rays->pos_y += rays->deltay;
    }
    else
    {
        if (map[rays->collision.col_pos_y][rays->collision.col_pos_x_sub_offset_x] == '0')
            rays->pos_x -= rays->deltax;
        if(map[rays->collision.col_pos_y_sub_offset_y][rays->collision.col_pos_x] == '0')
            rays->pos_y -= rays->deltay;
    }
    if(rays->pos_x < 0)
        rays->pos_x = 1;
    if(rays->pos_y < 0)
        rays->pos_y = 1;
}

void    rotate_gamer(t_ray *rays, char *direction)
{
    if(ft_strncmp(direction, "to_left", ft_strlen(direction)) == 0)
    {
        rays->gamer_angle -= 0.1;
        if (rays->gamer_angle < 0)
            rays->gamer_angle += 2* PI;
    }
    else
    {
        rays->gamer_angle += 0.1;
        if (rays->gamer_angle > 2 * PI)
            rays->gamer_angle -= 2* PI;
    }
    rays->deltax = cos(rays->gamer_angle) * 5;
    rays->deltay = sin(rays->gamer_angle) * 5;
}

int	event_key(int keycode, t_map *map)
{
	check_collision(&map->rays);
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}
	if (keycode == KEY_A)
        rotate_gamer(&map->rays, "to_left");
	if (keycode == KEY_D)
        rotate_gamer(&map->rays, "to_right");
 	if (keycode == KEY_W)
 	{
		// esse primeiro if faz com que ele "deslize" no eixo x quando contra uma parede
		// garantindo tambem um "offset" no eixo x, ou seja, se houver '1' no offset de x
		// (lateral do gamer) ele não avança mais, só enquanto for '0'..
        move_gamer(map->map, &map->rays, "to_up");
 	}
 	if (keycode == KEY_S)
 	{
		// poder "recuar" no eixo x.. se houver '1', ele nao recua
        move_gamer(map->map, &map->rays, "to_down");
 	}
	mlx_destroy_image (map->mlx.mlx_ptr, map->map2d.ptr_img);
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	color_background(map);
	paint_map(map);
	paint_gamer(map);
	return 0;
}

static int	check_resolution(t_map *map)
{
	int	resolutionX;
	int	resolutionY;

	mlx_get_screen_size(map->mlx.mlx_ptr, &resolutionX, &resolutionY);
	if (SCREEN_HEIGHT >= resolutionY || SCREEN_WIDTH >= resolutionX)
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

int open_texture(t_mlx *mlx, t_background *tile, int *coord, char *path)
{
    tile->ptr_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
        &coord[0], &coord[1]);
	if(!tile->ptr_img)
		return (404);
	tile->data = (int *)mlx_get_data_addr(tile->ptr_img, &tile->bpp, &tile->line_size, &tile->endian);
	return (0);
}

int	textures_init(t_image *textures, t_mlx *mlx)
{
    char *path;
    int  coord[2];

    coord[0] = textures->width;
    coord[1] = textures->height;
    path = textures->west_wall;
    if (open_texture(mlx, &textures->west_tile, coord, path) == 404)
		return (404);
    path = textures->east_wall;
    if (open_texture(mlx, &textures->east_tile, coord, path) == 404)
		return (404);
    path = textures->north_wall;
    if (open_texture(mlx, &textures->north_tile, coord, path) == 404)
		return (404);
    path = textures->south_wall;
    if (open_texture(mlx, &textures->south_tile, coord, path) == 404)
		return (404);
	return (0);
}

int	rays_struct_init(t_map *map)
{
	map->back.ptr_img = NULL;
	map->map2d.ptr_img = NULL;
	map->mlx.win = NULL;
	map->textures.east_tile.ptr_img = NULL;
	map->textures.west_tile.ptr_img = NULL;
	map->textures.north_tile.ptr_img = NULL;
	map->textures.south_tile.ptr_img = NULL;
	if (textures_init(&map->textures, &map->mlx) == 404)
		return (404);
	map->rays.map_x = map->width;
	map->rays.map_y = map->height;
	init_gamer_angle(map->spawing, &map->rays.gamer_angle);
	map->rays.deltax = cos(map->rays.gamer_angle) * 5;
	map->rays.deltay = sin(map->rays.gamer_angle) * 5;
	return (0);
}

void	game_loop(t_map *map)
{
	map->mlx.mlx_ptr = mlx_init();
	check_resolution(map);
	if (rays_struct_init(map) == 404)
		end_program(map);
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr,
        SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
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
