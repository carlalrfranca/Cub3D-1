/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:30 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/06 21:19:30 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int find_index(int curr_pixel_x, int curr_pixel_y, int map_width)
{
    return (curr_pixel_y * (map_width * map_s) + curr_pixel_x);
}

void	paint_gamer(t_map *map)
{
	int curr_pixel_y;
	int curr_pixel_x;
	int total_pixels_x;
	int total_pixels_y;
	int	pixel_index;

	curr_pixel_x = map->rays.pos_x;
	total_pixels_x = curr_pixel_x + 8;
	while (curr_pixel_x < total_pixels_x)
	{
		curr_pixel_y = map->rays.pos_y;
		total_pixels_y = curr_pixel_y + 8;
		while (curr_pixel_y < total_pixels_y)
		{
			pixel_index = find_index(curr_pixel_x, curr_pixel_y, map->width);
			map->map2d.data[pixel_index] = 0xFFCC00;
			curr_pixel_y++;
		}
		curr_pixel_x++;
	}
	cast_rays(map);
}

static void	paint_each_cell(t_map *map, int cell_in_x, int cell_in_y)
{
	int curr_pixel_y; //yo;// parte do pixel inicial da celula atual na vertical
	int curr_pixel_x; //xo;// parte do pixel inicial da celula atual na horizontal
	int pixel_index;

	curr_pixel_x = cell_in_x * map_s;
	while (curr_pixel_x < (map_s * (cell_in_x + 1)))
	{
		curr_pixel_y = cell_in_y * map_s;
		while (curr_pixel_y < (map_s * (cell_in_y + 1)))
		{
			pixel_index = find_index(curr_pixel_x, curr_pixel_y, map->width);
			if(map->map[cell_in_y][cell_in_x] == '1')
				map->map2d.data[pixel_index] = 0x000000;
			else if (map->map[cell_in_y][cell_in_x] == '0'
				|| map->map[cell_in_y][cell_in_x] == map->spawing)
				map->map2d.data[pixel_index] = 0xFFFFFF;
			else
				map->map2d.data[pixel_index] = 0x2C2F36;
			curr_pixel_y++;
		}
		curr_pixel_x++;
	}
}

static void	init_map2d_img(t_map *map)
{
	int	_2d_width;
	int _2d_height;

	//estabelece o tam do quadrado dentro da tela, por cima do background
	_2d_width = map->width * map_s;
	_2d_height = map->height * map_s;
	map->map2d.ptr_img = mlx_new_image(map->mlx.mlx_ptr,
		_2d_width, _2d_height);
	map->map2d.data = (int *)mlx_get_data_addr(map->map2d.ptr_img,
		&map->map2d.bpp, &map->map2d.line_size, &map->map2d.endian);
}

void	paint_map(t_map *map)
{
	int current_cell_x;
	int current_cell_y;
	int	total_cells_x;
	int	total_cells_y;

	init_map2d_img(map);
	total_cells_x = map->width;
	total_cells_y = map->height;
	current_cell_x = -1;
	while (++current_cell_x < total_cells_x)
	{
		current_cell_y = -1;
		while (++current_cell_y < total_cells_y)
			paint_each_cell(map, current_cell_x, current_cell_y);
	}
}
