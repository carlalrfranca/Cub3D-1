/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/17 10:13:39 by lfranca-         ###   ########.fr       */
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
	else if (!ft_strncmp(movement, "to_down", ft_strlen(movement)))
	{
		if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
			rays->pos_x -= rays->deltax;
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltay;
		// printf("Pos_x: %d	| sub offset x: %d\n", collision->pos_x, collision->pos_x_sub_offset_x);
	}
	else if (!ft_strncmp(movement, "to_left", ft_strlen(movement)))
	{
		//antes de tudo verifica se é angulo reto
		// o resto vem como else if
		// pq teremos o caso do deltaX ser negativo e quando ele nao é negativo so que
		// tem que ter un keito de diferentciar o 0 dos outros positivos
		// como nao da para ter um if (deltax == 0) porque o deltax é float
		// entao antes tem que ter um if verificando se o angulo do jogador é 90 graus ou 270 graus	
		printf("Entrou to_left\n");
		if (rays->deltax < 0) // ir para a esquerda olhando para oeste
		{
			// west = negativo
			// obs: verificar se, ao olhar para oeste, ele está no angulo reto 180 graus ou PI
			printf("Entrou delta_x negativo: DeltaX = %.2f\n", rays->deltax);
			if (rays->gamer_angle == (float)PI)
			{
				if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
					rays->pos_y -= rays->deltax;					
			}
			else if (rays->deltay < 0)
			{
				if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
					rays->pos_x += rays->deltax;
				if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
					rays->pos_y += rays->deltay;		
			}
			else
			{
				printf("Ele está olhando pro norte/quadrante inferior\n");
				if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
					rays->pos_x -= rays->deltax;
				if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
					rays->pos_y += rays->deltay;					
			}
		} 
		else if (rays->gamer_angle == (float)(PI/2) || rays->gamer_angle == (float)(3 * PI/2)) 
		{
			// essa condicao é para quando deltax == 0
			// porque teremos que usar o deltay pra mover em x
			printf("Entrou no angulo do jogador\n");
				if (rays->gamer_angle == (float)(3 * PI/2) && (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')) //sul ; alto
				{
					printf("Norte. DeltaY = %.1f | Pos_x: %.2f\n", rays->deltay, rays->pos_x);
					rays->pos_x += rays->deltay;
				}
				if (rays->gamer_angle == (float)(PI/2) && (map[collision->pos_y][collision->pos_x_add_offset_x] == '0'))
				{
					rays->pos_x += rays->deltay;
				}
				
		}
		else
			printf("Nem negativo, nem angulo reto. DeltaX = %.2f\n", rays->deltax);
		//else {
			// o delta x é maior que zero (podendo ser 0.1 pode ser zero mais ainda eh decimal).
			// east == positivo
			
		//}
			// quando for positivo 0 e 360 eh quando o y
	}
	// else if (!ft_strncmp(movement, "to_right", ft_strlen(movement)))
	// {
		// 
	// }



	// else if (!ft_strncmp(movement, "to_left", ft_strlen(movement)))
	// {
	// 	if (rays->deltay < 0)
	// 	{
	// 		if (rays->gamer_angle == (float)(3 * PI / 2))
	// 		{
	// 			// printf("Entrou aqui e off_set_x é: %d\n", collision->pos_x_add_offset_x);
	// 			// printf("Celula posição em x atual: %d\n", collision->pos_x);
	// 			// printf("Pos_x: %.2f\n", rays->pos_x);
	// 			if (map[collision->pos_y][collision->pos_x - 1] == '0')
	// 				rays->pos_x -= ((rays->deltax + 1) * 3);
	// 		}
	// 		else 
	// 		{
	// 			// printf("E aqui, foi?\n");
	// 			// printf("Pos_x: %.1f\n", rays->pos_x);
	// 			// printf("Pos_y: %.2f\n", rays->pos_y);
	// 			// printf("Celula da pos_x atual: %d\n", rays->collision.pos_x);
	// 			// printf("Celula da pos_y atual: %d\n", rays->collision.pos_y);
	// 			// printf("Celula ~adjacente~: %d\n", collision->pos_y);
	// 			// printf("Celula do off_add_x: %d\n", collision->pos_x_add_offset_x);
	// 			// rays->pos_x += rays->deltay;
	// 			if (map[collision->pos_y][collision->pos_x - 1] == '0')
	// 			{
	// 				rays->pos_x += (rays->deltax);
	// 				// printf("Pos_x: %.1f\n", rays->pos_x);
	// 			}
	// 			if (map[collision->pos_y - 1][collision->pos_x] == '0')
	// 			{
	// 				// printf("Pos_y: %.3f\n", rays->pos_y);
	// 				// printf("Delta Y: %.3f\n", rays->deltay);
	// 				rays->pos_y += (rays->deltay);
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (rays->gamer_angle == (float)(PI / 2))
	// 		{
	// 			if (map[collision->pos_y][collision->pos_x + 1] == '0')
	// 				rays->pos_x += ((rays->deltax + 1) * 3);
	// 		}
	// 		else
	// 		{
	// 			if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
	// 			{
	// 				rays->pos_x += rays->deltax;
	// 				if (rays->deltax == 0.0)
	// 					rays->pos_x += 6.0;
	// 			}
	// 			if (map[rays->collision.pos_y_sub_offset_y][collision->pos_x] == '0')
	// 			{
	// 				rays->pos_y += rays->deltay;
	// 				if (rays->deltay == 0.0)
	// 					rays->pos_y += 6.0;	
	// 			}
	// 		}
	// 	}
	// }
	// else if (!ft_strncmp(movement, "to_right", ft_strlen(movement)))
	// {
	// 	if (rays->deltay < 0)
	// 	{
	// 		if (rays->gamer_angle == (float)(3 * PI / 2))
	// 		{
	// 			printf("Entrou aqui e off_set_x é: %d\n", collision->pos_x_add_offset_x);
	// 			printf("Celula posição em x atual: %d\n", collision->pos_x);
	// 			printf("Pos_x: %.2f\n", rays->pos_x);
	// 			if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
	// 				rays->pos_x += ((rays->deltax + 1) * 2);
	// 		}
	// 		// if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
	// 		// {
	// 			// 
	// 		// }
	// 	}
	// }
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
	printf("Delta X: %.3f\n", rays->deltax);
	rays->deltay = sin(rays->gamer_angle) * 5;
	printf("Delta Y: %.3f\n", rays->deltay);
}

int	event_key(int keycode, t_map *map)
{
	check_collision(&map->rays);
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}
	if (keycode == ROTATE_LEFT)
		rotate_gamer(&map->rays, "to_left");
	if (keycode == ROTATE_RIGHT)
		rotate_gamer(&map->rays, "to_right");
	if (keycode == KEY_W)
		move_gamer(map->map, &map->rays, "to_up");
	if (keycode == KEY_S)
		move_gamer(map->map, &map->rays, "to_down");
	if (keycode == KEY_A)
		move_gamer(map->map, &map->rays, "to_left");
	if (keycode == KEY_D)
		move_gamer(map->map, &map->rays, "to_right");
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
