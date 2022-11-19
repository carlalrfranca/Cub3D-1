/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:26 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/14 22:50:55 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	color_background(t_map *map) //pintar a tela
{  
    int columns = -1;
    int rows;

	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img, &map->back.bpp,
		&map->back.line_size, &map->back.endian);
    while (++columns < SCREEN_HEIGHT)
    {
        rows = -1;
        while (++rows < SCREEN_WIDTH)
			map->back.data[columns * SCREEN_WIDTH + rows] = 0x5C5C5C;;
    }
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->back.ptr_img, 0, 0);
}
