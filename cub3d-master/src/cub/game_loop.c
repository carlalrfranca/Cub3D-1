/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/12 11:00:31 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <stdint.h>
#include <sys/time.h>

/*
valgrind --leak-check=full --show-leak-kinds=all ./cub3d ./maps/map.cub

render_mini_map()
E precisaremos deles na funcao renderMiniMap(0,0,0.75,rays) esta funcao recebe a posição X e Y, a escala 0.75 e a lista de rays

get_rays() -> tuto
Para obter os raios usamos a funcao onde o resultado 
	sera armazenado em uma constante de nome rays.
	podemos armazenar em um array e colocamos em uma estrutura

renderScenes(t_ray	rays)
vai chamar o algoritmo de function get_rays() e ir renderizando - pintando a tela

move_player();
atualizarf os valores
vai mover o player com os eventos do teclado

game_loop()
aqui se concentrara toda a logica de renderizacao
*****antes do loop_principal
precisamos inicializar a minilibx
abrir a janela

entrar no loop da minilibx
limpar a janela function clear_screen()
pinta a janela function render_scenes() com os valores do mapa recebido
redesenhar com novos valores function move_player();
*/

/*
int	event_key(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}
	if (keycode == KEY_A)
		move_gammer(map, map->x, map->y - 1);
	if (keycode == KEY_D)
		move_gammer(map, map->x, map->y + 1);
	if (keycode == KEY_S)
		move_gammer(map, map->x + 1, map->y);
	if (keycode == KEY_W)
		move_gammer(map, map->x - 1, map->y);
	return (0);
}
*/

// void	render_minimap(t_map *map) //continuar funcao
// {

// 	map->north = 0;
// 	printf("na render mini map");
// }

int *array_to_int(char *rgb_value)
{
	char	**rgb;
	int		*int_array;

	int_array = malloc(sizeof(int) * 3);
	rgb = ft_split(rgb_value, ',');
	int_array[0] = ft_atoi(rgb[0]);
	int_array[1] = ft_atoi(rgb[1]);
	int_array[2] = ft_atoi(rgb[2]);
	return(int_array);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}


void	check_color(t_map *map)
{
	map->rays.rgb = array_to_int("255, 0, 0");
	if (map->rays.side != 1)
		map->rays.color = encode_rgb(map->rays.rgb[0], map->rays.rgb[1], map->rays.rgb[2]);
	else
		map->rays.color = encode_rgb(110, 9, 9);
}

void	draw_stripe(t_map *map)
{
	map->rays.draw_start_temp = map->rays.draw_start;
	check_color(map);
	while(map->rays.draw_start_temp < map->rays.draw_end)
	{
		map->rays.count_pixel_square = 0;
		while (map->rays.count_pixel_square < 32)
		{
			mlx_pixel_put(map->mlx.mlx_ptr, map->mlx.win, (map->rays.x + map->rays.count_pixel_square), map->rays.draw_start_temp, map->rays.color);
			map->rays.count_pixel_square++;
		}
		map->rays.draw_start_temp++;
	}
}

void	check_distance_height_pixel(t_map *map)
{
	if(map->rays.side == 0)
		map->rays.perp_wall_dist = (map->rays.side_dist_x - map->rays.delta_dist_x);
	else
	  	map->rays.perp_wall_dist = (map->rays.side_dist_y - map->rays.delta_dist_y);
	//calcula altura da linha para desenhar na tela
	map->rays.line_height = (int)(SCREEN_HEIGHT / map->rays.perp_wall_dist); //calcula altura da linha desenhada na tela
	//calcula pixel mais baixo e mais alto para preencher faixa atual
	map->rays.draw_start = -map->rays.line_height / 2 + SCREEN_HEIGHT / 2;
	printf("Começo da parede: %d\n", map->rays.draw_start);
	if(map->rays.draw_start < 0)
		map->rays.draw_start = 0;
	map->rays.draw_end = map->rays.line_height / 2 + SCREEN_HEIGHT / 2;
	if(map->rays.draw_end >= SCREEN_HEIGHT)
		map->rays.draw_end = SCREEN_HEIGHT - 1;
}

void	check_ray_hit_wall(t_map *map)
{
	while(map->rays.hit == 0)
	{
		if(map->rays.side_dist_x < map->rays.side_dist_y) //vai para a proxima celula x ou y
	    {
	      map->rays.side_dist_x += map->rays.delta_dist_x;
	      map->rays.map_x += map->rays.step_x;
	      map->rays.side = 0;
	    }
	    else
	    {
	      map->rays.side_dist_y += map->rays.delta_dist_y;
	      map->rays.map_y += map->rays.step_y;
	      map->rays.side = 1;
	    }//Check if ray has hit a wall
		if(map->map[map->rays.map_x][map->rays.map_y] == '1')
			map->rays.hit = 1;
	}
}

void	calculate_initial_step_x(t_map *map)
{
	if (map->rays.ray_dir_x < 0)
	{
		map->rays.step_x = -1;
	    map->rays.side_dist_x = (map->rays.pos_x - map->rays.map_x) * map->rays.delta_dist_x;
	}
	else
	{
		map->rays.step_x = 1;
	    map->rays.side_dist_x = (map->rays.map_x + 1.0 - map->rays.pos_x) * map->rays.delta_dist_x;
	}
}
	
void	calculate_initial_step_y(t_map *map)
{
	if(map->rays.ray_dir_y < 0)
	{
		map->rays.step_y = -1;
	    map->rays.side_dist_y = (map->rays.pos_y - map->rays.map_y) * map->rays.delta_dist_y;
	}
	else
	{
	    map->rays.step_y = 1;
	    map->rays.side_dist_y = (map->rays.map_y + 1.0 - map->rays.pos_y) * map->rays.delta_dist_y;
	}
}

void	calculate_ray_length(t_map *map)
{//comprimento do raio de um lado x ou y para o proximo lado correspondente
	if((int)map->rays.ray_dir_x == 0)
		map->rays.delta_dist_x = 1e30;
	else 
		map->rays.delta_dist_x = abs(1 / (int)map->rays.ray_dir_x);
	if((int)map->rays.ray_dir_y == 0)
		map->rays.delta_dist_y = 1e30;
	else
		map->rays.delta_dist_y = abs(1 / (int)map->rays.ray_dir_y);
}

void	calculate_init_ray(t_map *map)
{
	map->rays.camera_x = 2 * map->rays.x / SCREEN_HEIGHT - 1; //coordenada no espaço da camera
	map->rays.ray_dir_x = map->rays.dir_x + map->rays.plane_x * map->rays.camera_x;
	map->rays.ray_dir_y = map->rays.dir_y + map->rays.plane_y * map->rays.camera_x;
	map->rays.map_x = (int)map->rays.pos_x;
	map->rays.map_y = (int)map->rays.pos_y;
}

void	get_rays(t_map *map)
{
	map->rays.dir_x = -1;
	map->rays.dir_y = 0;
	map->rays.plane_x = 0;
	map->rays.plane_y = 0.66;
	// map->rays.time = 0;
	// map->rays.old_time =0;
	map->rays.x = 0;
	map->rays.pos_x = 12.0;
	map->rays.pos_y = 2.0;
	while(map->rays.x < SCREEN_WIDTH) //calcula a posição e direção do raio
	{
		calculate_init_ray(map);
		map->rays.hit = 0;
		calculate_ray_length(map);
		calculate_initial_step_x(map);
		calculate_initial_step_y(map);
		check_ray_hit_wall(map);
		check_distance_height_pixel(map);//calcula distancia perpendicular
		//escolhe cor da parede
		//dar aos lados x e y diferentes brilhos
		// if (side == 1)
		// {
			// divide o vermelho por 2 (125, 0, 0)
		// }
		/* 'h' deve ser a macro SCREEN_HEIGHT (pq é em pixels)
			cria uma imagem (funcao minilibx) pra poder "pintar"
			usando data (e outros ponteiros) e, ao final, usar
			a funcao put_image da minilibx
			essa parte toda corresponde à linha 196 (verLine()) do tutorial
			pra desenhar os pixels de toda a coluna, vai ter que ter um while\
			para do draw_start ao drawEnd?
		*/ 
		draw_stripe(map);
		map->rays.x++;
	}
	//timing pra input e contador de FPS
	// old_time = time;
	// struct timeval current_time;
  	// gettimeofday(&current_time, NULL);
	// time = current_time.tv_sec;
	// double frameTime = (time - old_time) / 1000.0;

	// modificadores de velocidades
	// double moveSpeed = frameTime * 5.0;
	// double rotSpeed = frameTime * 3.0;

	//ao final, dar o equivalente ao cls(), que deve ser
	// destroy_image()	
}
/*
 abrir uma funcao para tratamento do
   spawing. Onde sera recvebido os valores iniciais
   de x e y e direcionados cada um para as variaveis 
   pos_x e pos_y na estrutura
*/

void	*open_img(t_map *map, char *path)
{
	void	*ptr;

	if (!map->height || !map->width)
	{
		write(2, "ERROR\n", 6);
		write(2, "Without image\n", 14);
		exit(1);
	}
	ptr = mlx_xpm_file_to_image(map->mlx.mlx_ptr, path, &map->width, &map->height);
	return (ptr);
}

// void	path_img(t_map *map)
// {
// 	map->img.north_wall = open_img(map, "../img/north_texture.png");
// 	map->img.south_wall = open_img(map, "../img/south_texture.png");
// 	map->img.west_wall = open_img(map, "../img/west_texture.png");
// 	map->img.east_wall = open_img(map, "../img/east_texture.png");		
// }

void	free_pointers(t_map *map)
{
	int i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free_map(map);
}

int	end_program(t_map *map)
{
	// if (map->textures.north_wall != 0)
		// mlx_destroy_image(map->mlx.mlx_ptr, map->textures.north_wall);
	// if (map->textures.south_wall != 0)
		// mlx_destroy_image(map->mlx.mlx_ptr, map->textures.south_wall);
	// if (map->textures.west_wall != 0)
		// mlx_destroy_image(map->mlx.mlx_ptr, map->textures.west_wall);
	// if (map->textures.east_wall != 0)
		// mlx_destroy_image(map->mlx.mlx_ptr, map->textures.east_wall);
	mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
	mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win);
	mlx_destroy_display(map->mlx.mlx_ptr);
	free_pointers(map);
	exit(0);
}

void	color_background(t_map *map, int width, int height)
{
	int	x;
	int	y;

	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, width, height);
	map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img,
			&map->back.bpp,
			&map->back.line_size, &map->back.endian);
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
			map->back.data[x * width + y] = 0x000000;
	}
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
		map->back.ptr_img, 0, 0);
}

void	render_scenes(t_map *map) //pintar a tela
{  
    int count_h = -1;
    int count_w;
	// int screen_width = map->width * 64;
	// int screen_height = map->height * 64;

	map->back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);

    map->back.data = (int *)mlx_get_data_addr(map->back.ptr_img, &map->back.bpp, &map->back.line_size, &map->back.endian);
    while (++count_h < SCREEN_HEIGHT)
    {
        count_w = -1;
        while (++count_w < SCREEN_WIDTH)
        {
            if (count_h < (SCREEN_HEIGHT/2))
                map->back.data[count_h * SCREEN_WIDTH + count_w] = 0;
            else
                map->back.data[count_h * SCREEN_WIDTH + count_w] = 0;
        }
    }
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, map->back.ptr_img, 0, 0);
}

// int	minimize_window(t_map *map)
// {
// 	mlx_destroy_image(map->mlx.mlx_ptr, map->back.ptr_img);
// 	render_scenes(map);//funcao diferente -calculo , raios e 3d* *****
// 	return (0);
// }

void	game_loop(t_map *map)
{
	// int	x;
	// int	y;
// 
	// x = map->width * 32;
	// y = map->height * 32;
	map->mlx.mlx_ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	while(map->mlx.win)
	{
		// path_img(map);//corrigir
		// clear_screen(map);
		mlx_hook(map->mlx.win, X_EVENT_KEY_EXIT, 1 << 0, end_program, map);
		render_scenes(map);//corrigir
		// mlx_hook(map->mlx.win, X_EVENT_KEY_PRESS, 1 << 0, event_key, map);
		get_rays(map);
		// mlx_expose_hook(map->mlx.win, minimize_window, &map);
		mlx_loop(map->mlx.mlx_ptr);
	}
}


