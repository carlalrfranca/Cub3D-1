/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_moves_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:54:59 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/18 20:00:30 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_vert_right_angles(char **map, t_ray *rays, char *movement)
{
	t_col	*collision;
	int		x_cell_to_check;
	int		side_to_move;

	collision = &rays->collision;
	if (!strncmp(movement, "to_left", ft_strlen(movement)))
	{
		x_cell_to_check = collision->pos_x_sub_offset_x;
		side_to_move = rays->deltay;
	}
	else
	{
		x_cell_to_check = collision->pos_x_add_offset_x;
		side_to_move = (rays->deltay * -1);
	}
	if (rays->gamer_angle == (float)(PI / 2)
		|| rays->gamer_angle == (float)(3 * PI / 2))
	{
		if (rays->gamer_angle == (float)(3 * PI / 2)
			&& (map[collision->pos_y][x_cell_to_check] == '0'))
			rays->pos_x += side_to_move;
		if (rays->gamer_angle == (float)(PI / 2)
			&& (map[collision->pos_y][x_cell_to_check] == '0'))
			rays->pos_x += side_to_move;
	}
}
