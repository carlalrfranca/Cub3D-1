/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:59:14 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 15:46:04 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	keep_angle_limits(float *ray_angle)
{
	if (*ray_angle < 0)
		*ray_angle += 2 * PI;
	if (*ray_angle > 2 * PI)
		*ray_angle -= 2 * PI;
}
