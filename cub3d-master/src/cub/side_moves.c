/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:50:41 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/18 19:59:55 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	to_left_looking_west(char **map, t_ray *rays)
{
	t_col	*collision;

	collision = &rays->collision;
	if (rays->gamer_angle == (float)PI)
	{
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
	else if (rays->deltay < 0)
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x += rays->deltay;
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
	else
	{
		if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
			rays->pos_x += rays->deltay;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
}

static void	to_left_looking_east(char **map, t_ray *rays)
{
	t_col	*collision;

	collision = &rays->collision;
	if (rays->gamer_angle == (float)0
		|| rays->gamer_angle == (float)(2 * PI))
	{
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
	else if (rays->deltay < 0)
	{
		if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
			rays->pos_x += rays->deltay;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
	else
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x += rays->deltay;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y -= rays->deltax;
	}
}

static void	to_right_looking_west(char **map, t_ray *rays)
{
	t_col	*collision;

	collision = &rays->collision;
	if (rays->gamer_angle == (float)PI)
	{
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
	else if (rays->deltay < 0)
	{
		if (map[collision->pos_y][collision->pos_x_sub_offset_x] == '0')
			rays->pos_x -= rays->deltay;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
	else
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x -= rays->deltay;
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
}

static void	to_right_looking_east(char **map, t_ray *rays)
{
	t_col	*collision;

	collision = &rays->collision;
	if (rays->gamer_angle == (float)0
		|| rays->gamer_angle == (float)(2 * PI))
	{
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
	else if (rays->deltay < 0)
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x -= rays->deltay;
		if (map[collision->pos_y_sub_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
	else
	{
		if (map[collision->pos_y][collision->pos_x_add_offset_x] == '0')
			rays->pos_x -= rays->deltay;
		if (map[collision->pos_y_add_offset_y][collision->pos_x] == '0')
			rays->pos_y += rays->deltax;
	}
}

void	move_gamer_to_sides(char **map, t_ray *rays, char *movement)
{
	if (!ft_strncmp(movement, "to_left", ft_strlen(movement)))
	{
		check_vert_right_angles(map, rays, "to_left");
		if (rays->deltax < 0)
			to_left_looking_west(map, rays);
		else
			to_left_looking_east(map, rays);
	}
	else if (!ft_strncmp(movement, "to_right", ft_strlen(movement)))
	{
		check_vert_right_angles(map, rays, "to_right");
		if (rays->deltax < 0)
			to_right_looking_west(map, rays);
		else
			to_right_looking_east(map, rays);
	}
}
