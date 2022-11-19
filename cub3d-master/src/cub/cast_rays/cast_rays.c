/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:08:08 by lfranca-          #+#    #+#             */
/*   Updated: 2022/11/19 19:46:28 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

// texturas
int All_Textures[] =
{
	// Checkerboard
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

	// Bricks
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	// Window
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,

	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,

	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
	
	// Door
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,

	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
	0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
};

// 

int draw_line(t_map *map, int color)
{
	float	delta_x;
	float	delta_y;
	float	pixel_pos_x;
	float	pixel_pos_y;
	int		numberPixels;
	
	// coordenadas iniciais do raio a ser desenhado (posicao do pixel em x e y)
	pixel_pos_x = map->rays.pos_x;
	pixel_pos_y = map->rays.pos_y;

	delta_y = map->rays.ray_y - map->rays.pos_y; //endy - py; //0
	delta_x = map->rays.ray_x - map->rays.pos_x; //endx - px; //10
	numberPixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));

	//abaixo: calculo pra descobrir quantos pixels adicionar ao eixo x e ao eixo y
	//em cada iteração
	delta_x /= numberPixels; // 1
	delta_y /= numberPixels; // 0
	while (numberPixels)
	{
    	mlx_pixel_put(map->mlx.mlx_ptr, map->mlx.win, pixel_pos_x, pixel_pos_y, color);
    	pixel_pos_x += delta_x;
    	pixel_pos_y += delta_y;
    	--numberPixels;
	}
	return(0);
}

float measure_ray_dist(float beginX, float beginY, float endX, float endY)
{
	float catetoX_squared;
	float catetoY_squared;

	catetoX_squared = (endX - beginX) * (endX - beginX);
	catetoY_squared = (endY - beginY) * (endY - beginY);
	return (sqrt(catetoX_squared + catetoY_squared));
}

static void init_ray_projection_values(t_map *map, float *rayX, float *rayY)
{
	map->rays.depth_of_field = 0;
	map->rays.dist_horizontal = 1000000;
	*rayX = map->rays.pos_x;
	*rayY = map->rays.pos_y;
}

int	check_horizontal_hit(t_map *map, float *hx, float *hy)
{
	int mx;
	int my;

	// map->rays.depth_of_field = 0;
	// map->rays.dist_horizontal = 1000000;
	// *hx = map->rays.pos_x;
	// *hy = map->rays.pos_y;
	int htexture = 0;
	init_ray_projection_values(map, hx, hy);
	map->rays.neg_inv_tan = -1/tan(map->rays.ray_angle);
	if(map->rays.ray_angle > PI) //se tiver olhando para baixo
	{
		map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) - 0.0001;
		map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
		map->rays.step_y = -map_s;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	else if(map->rays.ray_angle < PI)//se tiver olhando pra cima
	{
		map->rays.ray_y = (((int)map->rays.pos_y>>5)<<5) + map_s;
		map->rays.ray_x = (map->rays.pos_y - map->rays.ray_y) * map->rays.neg_inv_tan + map->rays.pos_x;
		map->rays.step_y = map_s;
		map->rays.step_x = -map->rays.step_y * map->rays.neg_inv_tan;
	}
	if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI)//olhando direto para esquerda ou direita
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->height; //antes era 8 (dof)
	}
	while(map->rays.depth_of_field < map->height) //antes era < 8 (dof)
	{
		mx = (int)map->rays.ray_x >> 5;
		my = (int)map->rays.ray_y >> 5;
		// mp = my * map->rays.map_x + mx;
		if(((mx >= 0 && mx < map->width) && (my >= 0 && my < map->height)) && map->map[my][mx] == '1') //se bateu na parede entao para o loop //mp > 0 && mp < (map->rays.map_x * map->rays.map_y) && 
		{
			*hx = map->rays.ray_x;
			*hy = map->rays.ray_y;
			map->rays.dist_horizontal = measure_ray_dist(map->rays.pos_x, map->rays.pos_y, *hx, *hy);
			map->rays.depth_of_field = map->height; // hit muro (maxima de celulas de altura no mapa -> no modelo é 8 por 8)
		}
		else //se nao bateu incrementa o tamanho do raio
		{ //xo e yo é o comprimento interno da célula - do ponto inicial ao final
			map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
			map->rays.ray_y += map->rays.step_y;
			map->rays.depth_of_field += 1;
		}		
	}
	return (htexture);
}

int	check_vertical_hit(t_map *map, float *vx, float *vy)
{
	int mx;
	int my;

	map->rays.depth_of_field = 0; //triangulacao calculo de tirar inverso da tangente etc
	map->rays.dist_vertical = 1000000;
	*vx = map->rays.pos_x;
	*vy = map->rays.pos_y;
	int vtexture = 0;
	// init_ray_projection_values(map, vx, vy);
	map->rays.neg_tan = -tan(map->rays.ray_angle);
	if(map->rays.ray_angle > P2 || map->rays.ray_angle < P3) //olhando lado esquerdo
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) - 0.0001;
		map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
		map->rays.step_x = -map_s;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}
	if(map->rays.ray_angle < P2 || map->rays.ray_angle > P3) //olhando lado direito
	{
		map->rays.ray_x = (((int)map->rays.pos_x >> 5) << 5) + map_s;
		map->rays.ray_y = (map->rays.pos_x - map->rays.ray_x) * map->rays.neg_tan + map->rays.pos_y;
		map->rays.step_x = map_s;
		map->rays.step_y = -map->rays.step_x * map->rays.neg_tan;
	}		
	
	if(map->rays.ray_angle == 0 || map->rays.ray_angle == PI) //olhando para cima ou para baixo
	{
		map->rays.ray_x = map->rays.pos_x;
		map->rays.ray_y = map->rays.pos_y;
		map->rays.depth_of_field = map->width; // antes 8 (dof)
	}
	while(map->rays.depth_of_field < map->width) // dof é a profundidade de campo (antes 8 como no modelo do mapa 8 por 8)
	{
		mx = (int)(map->rays.ray_x)>>5;
		my = (int)(map->rays.ray_y)>>5;
		// mp = my * map->rays.map_x + mx;
		if(((mx >= 0 && mx < map->width) && (my >= 0 && my < map->height)) && map->map[my][mx] == '1') //se bateu na parede entao para o loop //mp > 0 && mp < (map->rays.map_x * map->rays.map_y) &&
		{
			*vx = map->rays.ray_x;
			*vy = map->rays.ray_y;
			map->rays.dist_vertical = measure_ray_dist(map->rays.pos_x, map->rays.pos_y, *vx, *vy);
			map->rays.depth_of_field = map->width; // hit muro (antes 8 de acordo com o mapa 8x8)
		}
		else //se nao bateu incrementa o tamanho do raio
		{ //xo e yo é o comprimento interno da célula - do ponto inicial ao final
			map->rays.ray_x += map->rays.step_x; //xo e yo posicao inicial do raio
			map->rays.ray_y += map->rays.step_y; //hit muro
			map->rays.depth_of_field += 1; //próxima linha
		}			
	}
	return (vtexture);
}

static void fix_fish_eye(t_ray *rays)
{
	float gamerToRayAngle;

	// 1- consertar efeito olho de peixe
	gamerToRayAngle = rays->gamer_angle - rays->ray_angle;
	if(gamerToRayAngle < 0)
		gamerToRayAngle += 2*PI;
	else if (gamerToRayAngle > 2*PI)
		gamerToRayAngle -= 2*PI;
	rays->dist_final = rays->dist_final * cos(gamerToRayAngle);
}

static int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

// static void draw_wall_slice(t_mlx *mlx, float centeredVision, float lineHeight, int ct_rays, int color)
// {
// 	int		initialLineWidth;
// 	int		totalLineWidth;
// 	int		finalLineWidth;
// 	float	currHeight;

// 	totalLineWidth = 8;
// 	currHeight = centeredVision; //começará a ser desenhado abaixo da metade pra ficar centralizado
// 	while(currHeight < (lineHeight + centeredVision))
// 	{
// 		initialLineWidth = ct_rays * totalLineWidth;
// 		finalLineWidth = initialLineWidth + totalLineWidth;
// 		while(initialLineWidth < finalLineWidth)
// 		{
// 			mlx_pixel_put(mlx->mlx_ptr, mlx->win, 400+initialLineWidth, currHeight, color);
// 			initialLineWidth++;
// 		}
// 		currHeight++;
// 	}
// }

static void draw_3d(t_ray *ray, t_mlx *mlx, float dist_final, int color, int ct_rays, float shade, int steptexture)
{	
	float	centeredVision;
	float	lineHeight;

	// 2- tirar a altura da coluna/tira de parede a ser desenhada
	lineHeight = (map_s * 500/dist_final);
	float ty_step = 32.0/lineHeight;
	// ty_off vai compensar o mapeamento da textura em y caso a altura
	// da parede estoure a altura da janela
	// pra que, na hora que estiver desenhando a textura
	// e chegar superar o tamanho de janela da projeção 3d, o
	// desenho não fique distorcido (perca a perspectiva)
	float ty_off = 0;
	if(lineHeight > 500)
	{
		ty_off = (lineHeight - 500)/2.0;
		lineHeight = 500 - 1;
	}
	// precisamos centralizar a imagem (desenhar a tira da parede a partir de metade abaixo do total da altura da tela)
	centeredVision = 250 - lineHeight/2;
	// draw_wall_slice(mlx, centeredVision, lineHeight, ct_rays, color);
	// 'ty' calcula o valor 'y' das texturas
	int y;
	float ty = ty_off * ty_step + (32 * steptexture);
	float tx;
	if(shade == 1)
	{
		tx = (int)(ray->ray_x/2.0) % 32;
		if(ray->ray_angle > PI)
		{
			tx = 31 - tx;
			ty += 32 * 2;
		}
	}
	else
	{
		tx = (int)(ray->ray_y/2.0) % 32;
		if (ray->ray_angle > P2 && ray->ray_angle < P3)
		{
			tx = 31 - tx;
			ty += 32 * 2;
		}
		else
			ty += 32;
		// pra pintar uma textura diferente do lado esquerdo da parede só incrementar o ty pra textura
	}
	float c;
	int pixelSize;
	int	totalSize;
	
	// ty+=32;

	for(y=0; y<lineHeight; y++)
	{
		c = All_Textures[(int)(ty)*32 + (int)(tx)];
		if(c == 0)
			color = encode_rgb(255, 255, 255);
		else
			color = encode_rgb(0, 0, 0);
		// ct_rays = contador de qual raio está no momento -> cada raio projeta um pedaço/uma fina coluna da parede
		color *= shade;
		pixelSize = ct_rays * 8;
		totalSize = pixelSize + 8;
		while (pixelSize < totalSize)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, pixelSize + 400, y + centeredVision, color);
			pixelSize++;
		}
		ty += ty_step;
	}
}

void	keep_angle_limits(float *ray_angle)
{
	if (*ray_angle < 0)
		*ray_angle += 2 * PI;
	if (*ray_angle > 2 * PI)
		*ray_angle -= 2 * PI;
}

void cast_rays(t_map *map)
{
	int		ct_rays; //r;
	int		color;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	int		htexture;
	int		vtexture;

	map->rays.ray_angle = map->rays.gamer_angle - DR * 30; //angulo do raio
	keep_angle_limits(&map->rays.ray_angle);
	ct_rays = -1;
	while(++ct_rays < 120)
	{
		// -------------- linhas horizontais
		htexture = check_horizontal_hit(map, &hx, &hy);
		// draw_line(map, 0xFFCC00);

		// -------------- linhas verticais
		vtexture = check_vertical_hit(map, &vx, &vy);

		// --------------- determine which ray is smaller so we cast it
		float shade;
		shade = 1;
		// if the vertical ray is smaller, we change the shade value
		if (map->rays.dist_vertical < map->rays.dist_horizontal)
		{
			htexture = vtexture;
			map->rays.ray_x = vx;
			map->rays.ray_y = vy;
			map->rays.dist_final = map->rays.dist_vertical;
			shade = 0.6;
			color = encode_rgb(54, 204, 207);
		}
		else if (map->rays.dist_horizontal < map->rays.dist_vertical)
		{
			map->rays.ray_x = hx;
			map->rays.ray_y = hy;
			map->rays.dist_final = map->rays.dist_horizontal;
			color = encode_rgb(38, 153, 189);
		}
		draw_line(map, color);

		// --------------- Desenhar paredes 3D -----------
		fix_fish_eye(&map->rays);
		draw_3d(&map->rays, &map->mlx, map->rays.dist_final, color, ct_rays, shade, htexture);

		// --------------- incrementa angulo para o próximo raio
		map->rays.ray_angle += DR/2;
		keep_angle_limits(&map->rays.ray_angle);
	}
}
