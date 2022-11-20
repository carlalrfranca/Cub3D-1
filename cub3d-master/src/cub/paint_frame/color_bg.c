/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:26 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/19 22:34:02 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	color_background(t_map *map) //pintar a tela
{  
    int columns = -1;
    int rows;
	char **rgb_split_ceilling;
	char **rgb_split_floor;
	int ceilling_color;
	int	floor_color;

	rgb_split_ceilling = ft_split(map->ceilling, ',');
	rgb_split_floor = ft_split(map->floor, ',');
	ceilling_color = encode_rgb(ft_atoi(rgb_split_ceilling[0]), ft_atoi(rgb_split_ceilling[1]), ft_atoi(rgb_split_ceilling[2]));
	floor_color = encode_rgb(ft_atoi(rgb_split_floor[0]), ft_atoi(rgb_split_floor[1]), ft_atoi(rgb_split_floor[2]));
	// printf("Cor do teto e do piso em inteiro: %d e %d\n", ceilling_color, floor_color);
	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img, &map->back.bpp,
		&map->back.line_size, &map->back.endian);
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
	free_matrix(rgb_split_ceilling);
	free_matrix(rgb_split_floor);
	free(rgb_split_ceilling);
	free(rgb_split_floor);
    // mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->back.ptr_img, 0, 0);
}
