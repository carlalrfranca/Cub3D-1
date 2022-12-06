/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:30 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/06 20:17:42 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int find_index(int pixel_horiz, int pixel_vert, int map_width)
{
    return (pixel_vert * (map_width * map_s) + pixel_horiz);
}

void	paint_gamer(t_map *map)
{
	int pixel_horiz;//x;
	int pixel_vert;//y;
	int	pixel_index;
	int total_pixels_horiz;
	int total_pixels_vert;

	pixel_horiz = map->rays.pos_x;
	total_pixels_horiz = pixel_horiz + 8;
	while (pixel_horiz < total_pixels_horiz)
	{
		pixel_vert = map->rays.pos_y;
		total_pixels_vert = pixel_vert + 8;
		while (pixel_vert < total_pixels_vert)
		{
			pixel_index = find_index(pixel_horiz, pixel_vert, map->width);
			map->map2d.data[pixel_index] = 0xFFCC00;
			pixel_vert++;
		}
		pixel_horiz++;
	}
	cast_rays(map);
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
					if(map->map[cell_vertical][cell_horizontal] == '1')
						map->map2d.data[px_begin_vertical * (map->width * map_s) + px_begin_horizontal] = 0x000000;
					else if (map->map[cell_vertical][cell_horizontal] == '0' || map->map[cell_vertical][cell_horizontal] == map->spawing)
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
}
