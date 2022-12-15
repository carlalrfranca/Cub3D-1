/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/14 20:56:23 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_collision(t_ray *rays)
{
	int	offset_x;
	int	offset_y;

	offset_x = 0;
	offset_y = 0;
	if (rays->deltax < 0)
		offset_x = -20;
	else
		offset_x = 20;
	if (rays->deltay < 0)
		offset_y = -20;
	else
		offset_y = 20;
	rays->collision.pos_x = rays->pos_x / 32.0;
	rays->collision.pos_y = rays->pos_y / 32.0;
	rays->collision.pos_x_add_offset_x = (rays->pos_x + offset_x) / 32.0;
	rays->collision.pos_y_add_offset_y = (rays->pos_y + offset_y) / 32.0;
	rays->collision.pos_y_sub_offset_y = (rays->pos_y - offset_y) / 32.0;
	rays->collision.pos_x_sub_offset_x = (rays->pos_x - offset_x) / 32.0;
}

void	move_gamer(char **map, t_ray *rays, char *movement)
{
	t_col	*collision;

	collision = &rays->collision;
	if (!ft_strncmp(movement, "to_up", ft_strlen(movement)))
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x += rays->deltax;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltay;
	}
	else
	{
		if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
			rays->pos_x -= rays->deltax;
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltay;
	}
}

void	rotate_gamer(t_ray *rays, char *direction)
{
	if (ft_strncmp(direction, "to_left", ft_strlen(direction)) == 0)
	{
		rays->gamer_angle -= 0.1;
		if (rays->gamer_angle < 0)
			rays->gamer_angle += 2 * PI;
	}
	else
	{
		rays->gamer_angle += 0.1;
		if (rays->gamer_angle > 2 * PI)
			rays->gamer_angle -= 2 * PI;
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
		move_gamer(map->map, &map->rays, "to_up");
	if (keycode == KEY_S)
		move_gamer(map->map, &map->rays, "to_down");
	mlx_destroy_image (map->mlx.mlx_ptr, map->back.ptr_img);
	color_background(map);
	cast_rays(map);
	return (0);
}

void	game_loop(t_map *map)
{
	map->mlx.mlx_ptr = mlx_init();
	check_resolution(map);
	if (rays_struct_init(map) == 404)
	{
		ft_putendl_fd("Error\nTexture not found.", 2);
		end_program(map);
	}
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	color_background(map);
	cast_rays(map);
	mlx_hook(map->mlx.win, X_EVENT_KEY_PRESS, 1L << 0, event_key, map);
	mlx_hook(map->mlx.win, X_EVENT_KEY_EXIT, 1L << 0, end_program, map);
	mlx_expose_hook(map->mlx.win, minimize_window, map);
	mlx_loop(map->mlx.mlx_ptr);
}
