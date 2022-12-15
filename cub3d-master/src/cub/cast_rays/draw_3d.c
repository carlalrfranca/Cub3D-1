/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/14 20:13:40 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	fix_fish_eye(t_ray *rays)
{
	float	gamer_to_ray_angle;

	gamer_to_ray_angle = rays->gamer_angle - rays->ray_angle;
	if (gamer_to_ray_angle < 0)
		gamer_to_ray_angle += 2 * PI;
	else if (gamer_to_ray_angle > 2 * PI)
		gamer_to_ray_angle -= 2 * PI;
	rays->dist_final *= cos(gamer_to_ray_angle);
}

static int	find_texture_pixel(t_3dmap *scene)
{
	return ((int)(scene->texture_y) * MAP_S + (int)(scene->texture_x));
}

void	draw_wall_strip(t_3dmap *scene, t_map *map, int rays_counter)
{
	int		y;
	float	pixel_color;
	int		pixel_size;
	int		total_size;

	y = -1;
	while (++y < scene->line_height)
	{
		pixel_color = (scene->data_tile)[find_texture_pixel(scene)];
		if (map->rays.dist_vertical < map->rays.dist_horizontal)
			pixel_color = ((int)pixel_color & 0xfefefe) >> 1;
		pixel_size = rays_counter * 2;
		total_size = pixel_size + 2;
		while (pixel_size < total_size)
		{
			map->back.data[(y + (int)scene->centered_vision)
				* SCREEN_WIDTH + (pixel_size)] = pixel_color;
			pixel_size++;
		}
		scene->texture_y += scene->texture_y_step;
	}
}

void	define_walltexture(t_3dmap *scene, t_ray *rays, t_textures *textures)
{
	if (rays->dist_horizontal < rays->dist_vertical)
	{
		scene->texture_x = (int)(rays->ray_x) % MAP_S;
		if (rays->ray_angle > PI)
			scene->data_tile = textures->south_tile.data;
		else
			scene->data_tile = textures->north_tile.data;
	}
	else
	{
		scene->texture_x = (int)(rays->ray_y) % MAP_S;
		if (rays->ray_angle > (PI / 2) && rays->ray_angle < (3 * PI / 2))
			scene->data_tile = textures->west_tile.data;
		else
			scene->data_tile = textures->east_tile.data;
	}
}

/* 1 - tirar a altura da coluna/tira de parede a ser desenhada */
/* texture_y_off vai compensar o mapeamento da textura em y caso a altura */
/* da parede estoure a altura da janela */
/* pra que, na hora que estiver desenhando a textura */
/* e chegar superar o tamanho de janela da projeção 3d, o */
/* desenho não fique distorcido (perca a perspectiva) */
/* precisamos centralizar a imagem (desenhar a tira da parede*/
/* a partir de metade abaixo do total da altura da tela) */
/* 'texture_y' calcula o valor 'y' das texturas */
/* defines_wall_texture() --> chooses the texture and set the texture_x */
void	draw_3d(t_ray *rays, float dist_final, int rays_counter, t_map *map)
{
	t_3dmap	scene;

	scene.line_height = (MAP_S * SCREEN_HEIGHT / dist_final);
	scene.texture_y_step = 32.0 / scene.line_height;
	scene.texture_y_off = 0;
	if (scene.line_height > SCREEN_HEIGHT)
	{
		scene.texture_y_off = (scene.line_height - SCREEN_HEIGHT) / 2.0;
		scene.line_height = SCREEN_HEIGHT - 1;
	}
	scene.centered_vision = (SCREEN_HEIGHT / 2) - (scene.line_height / 2);
	scene.texture_y = scene.texture_y_off * scene.texture_y_step;
	define_walltexture(&scene, rays, &map->textures);
	draw_wall_strip(&scene, map, rays_counter);
}
