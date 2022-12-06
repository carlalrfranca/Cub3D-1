/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:26 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/06 20:03:53 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int get_color(char *rgb)
{
	char **rgb_split;
	int color;

	rgb_split = ft_split(rgb, ',');
	color = encode_rgb(ft_atoi(rgb_split[0]),
		ft_atoi(rgb_split[1]), ft_atoi(rgb_split[2]));
	free_matrix(rgb_split);
	free(rgb_split);
	return (color);
}

void	color_background(t_map *map) //pintar a tela
{  
    int columns;
    int rows;
	int ceilling_color;
	int floor_color;

	ceilling_color = get_color(map->ceilling);
	floor_color = get_color(map->floor);
	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img, &map->back.bpp,
		&map->back.line_size, &map->back.endian);
	columns = -1;
    while (++columns < SCREEN_HEIGHT)
    {
        rows = -1;
        while (++rows < SCREEN_WIDTH)
		{
			if (columns < SCREEN_HEIGHT/2)
				map->back.data[columns * SCREEN_WIDTH + rows] = ceilling_color;
			else
				map->back.data[columns * SCREEN_WIDTH + rows] = floor_color;
		}
    }
}
