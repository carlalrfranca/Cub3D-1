/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:30 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/12 21:08:51 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	paint_gamer(t_map *map)
{
	int pixel_horizontal;//x;
	int pixel_vertical;//y;

	map->gamer.ptr_img = mlx_new_image(map->mlx.mlx_ptr, 8, 8);
	map->gamer.data = (int *)mlx_get_data_addr(map->gamer.ptr_img,
		&map->gamer.bpp, &map->gamer.line_size, &map->gamer.endian);
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
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
		map->gamer.ptr_img, map->rays.pos_x, map->rays.pos_y);
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
	map->map2d.ptr_img = mlx_new_image(map->mlx.mlx_ptr, map->width * map_s, map->height * map_s);
	map->map2d.data = (int *)mlx_get_data_addr(map->map2d.ptr_img, &map->map2d.bpp, &map->map2d.line_size, &map->map2d.endian);
	cell_horizontal = 0;
	while (cell_horizontal < map->width)
	{
		cell_vertical = 0;
		while (cell_vertical < map->height)
		{
			px_begin_horizontal = cell_horizontal * map_s;
			// inserir esses dois while() internos na função: paint_pixel()
			while (px_begin_horizontal < (map_s * (cell_horizontal + 1)))
			{
				px_begin_vertical = cell_vertical * map_s;
				while (px_begin_vertical < (map_s * (cell_vertical + 1)))
				{
					//printf("cell_h: %d e cell_v: %d\n", cell_horizontal, cell_vertical);
					if(map->map[cell_vertical][cell_horizontal] == '1')
						map->map2d.data[px_begin_vertical * (map->width * map_s) + px_begin_horizontal] = 0x000000;
					else if (map->map[cell_vertical][cell_horizontal] == '0')
						map->map2d.data[px_begin_vertical * (map->width * map_s) + px_begin_horizontal] = 0xFFFFFF;
					else
						map->map2d.data[px_begin_vertical * (map->width * map_s) + px_begin_horizontal] = 0x2C2F36;
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
