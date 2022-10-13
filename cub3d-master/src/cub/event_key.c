/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:42:11 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/13 15:49:48 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
atualiza valores - move o player com eventos do teclado
get_rays dentro da logica dos eventos
depois de atualizar as posicoes x e y do player

incluir rotacao left e right struct para movimento
move.right
move.left
*/

int	event_key(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}
	if (keycode == KEY_A)
		move_player(map, map->rays.pos_x, map->rays.pos_y - 1);
	if (keycode == KEY_D)
		move_player(map, map->rays.pos_x, map->rays.pos_y + 1);
	if (keycode == KEY_S)
		move_player(map, map->rays.pos_x + 1, map->rays.pos_y);
	if (keycode == KEY_W)
		move_player(map, map->rays.pos_x - 1, map->rays.pos_y);
	if (keycode == ROTATE_LEFT)
		move_player(map, map->rotation.left, map->rays.pos_y);
	if (keycode == ROTATE_RIGHT)
		move_player(map, map->rotation.right, map->rays.pos_y);
	if (keycode == KEY_W && keycode == KEY_A)
		move_player(map, map->rays.pos_x - 1, map->rays.pos_y - 1);
	if (keycode == KEY_W && keycode == KEY_D)
		move_player(map, map->rays.pos_x - 1, map->rays.pos_y + 1);
	if (keycode == KEY_S && keycode == KEY_A)
		move_player(map, map->rays.pos_x + 1, map->rays.pos_y - 1);
	if (keycode == KEY_S && keycode == KEY_D)
		move_player(map, map->rays.pos_x + 1, map->rays.pos_y + 1);
	return (0);
}

void	move_player(t_map *map, int x, int y)
{
	if (x < map->height && y < map->width && x >= 0 && y >= 0)
	{//verificacao da parede
		if (map->map[x][y] != '1')
		{
			map->map[(int)map->rays.pos_x][(int)map->rays.pos_y] = '0';
			map->rays.pos_x = x;
			map->rays.pos_y = y;
			map->map[x][y] = map->spawing;
			mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
			get_rays(map);
		}
	}
}
