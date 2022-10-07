/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/07 19:55:10 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <stdint.h>
#include <sys/time.h>

/*
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

//void	free_map(t_map *map)
//{
//
//}

//void event_key()
//{
//	/*
//	**
//	*/
//}

/*



*/

// char	*dec_to_hexa(int color)
// {
// 	char	*hexa_dec;
// 	char	*hex_code;
// 	int		cnt_digit;
// 	int		index;
// 	int		temp;
// 	int		number;

// 	hex_code = "";
// 	cnt_digit = 0;
// 	index = 0;
// 	temp = 0;
// 	number = color;
// 	while (number)
// 	{
// 		number /= 10;
// 		cnt_digit++;	
// 	}
// 	while (color != 0)
// 	{
// 		temp = color % 16;
// 		if (temp < 10)
// 		{
// 			hexa_dec[index] = temp + 48;
// 			index++;
// 		}
// 		else
// 		{
// 			hexa_dec[index] = temp + 55;
// 			index++;
// 		}
// 		color = (color / 16);
// 	}
// 	if (index == 2)
// 		hex_code = ft_strjoin(hex_code, hexa_dec);
// 	else if (index == 1)
// 	{
// 		hex_code = "0";
// 		hex_code = ft_strjoin(hex_code, hexa_dec);
// 	}
// 	else if (index == 0)
// 	hex_code = "00";
// 	return(hex_code);
// }

//parametro *map nao usado
// char	*rgb_to_hexa(t_map *map)
// {
// 	int		red;
// 	int		green;
// 	int		blue;
// 	int		index;
// 	char	**rgb;
// 	char	*hex_code;
// 	char	*rgb_value;

// 	red = 0;
// 	green = 0;
// 	blue = 0;
// 	index = -1;
// 	rgb = ft_split(rgb_value, ',');
// 	if (rgb_value[index])
// 	{
// 		red = ft_atoi(rgb[0]);
// 		green = ft_atoi(rgb[1]);
// 		blue = ft_atoi(rgb[2]);
// 	}
// 	hex_code = 0;
// 	hex_code = ft_strjoin(hex_code, dec_to_hexa(red));
//     hex_code = ft_strjoin(hex_code, dec_to_hexa(green));
//     hex_code = ft_strjoin(hex_code, dec_to_hexa(blue));
// 	return(hex_code);
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

// void	render_minimap(t_map *map) //continuar funcao
// {

// 	map->north = 0;
// 	printf("na render mini map");
// }

void	get_rays(t_map *map)
{
	double dir_x; //vetor de direcao inicial
	double dir_y;
	double plane_x; // versao 2d raycaster do plano de camera
	double plane_y;
	// double time; //tempo do quadro atual
	// double old_time; //tempo do frame anterior
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int		x;
	int	map_x; //posicao atual na celula
	int	map_y;
	double	pos_x; //posicao
	double	pos_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
	int line_height;
	int draw_start;
	int	color;


	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	// time = 0;
	// old_time =0;
	x = 0;
	map->pos_x = 12.0;
	map->pos_y = 2.0;
	// printf("Posicao atual em x: %f e em %d\n", map->pos_x, (int)map->pos_x);
	// printf("Posicao atual em y: %f\n", map->pos_y);
	pos_x = map->pos_x;
	pos_y = map->pos_y;
	
	while(x < SCREEN_WIDTH) //calcula a posição e direção do raio
	{
		camera_x = 2 * x / SCREEN_HEIGHT - 1; //coordenada no espaço da camera
		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;
		map_x = (int)pos_x;
		map_y = (int)pos_y;
		hit = 0;
		// printf("rayDirx: %f \trayDiry: %f\n", ray_dir_x, ray_dir_y);
		// printf("Calculo: %i\n", abs(1/(int)ray_dir_y));
		// printf("rayDirx inteiro: %d\t rayDiry inteiro: %d\n", (int)ray_dir_x, (int)ray_dir_y);
		if((int)ray_dir_x == 0)
			delta_dist_x = 1e30;
		else 
			delta_dist_x = abs(1 / (int)ray_dir_x);
		if((int)ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = abs(1 / (int)ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
    	    side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
    	    side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
    	if(ray_dir_y < 0)
    	{
			step_y = -1;
    	    side_dist_y = (pos_y - map_y) * delta_dist_y;
    	}
		else
    	{
    	    step_y = 1;
    	    side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
    	}
    	while(hit == 0)
    	{
			if(side_dist_x < side_dist_y)
    	    {
    	      side_dist_x += delta_dist_x;
    	      map_x += step_x;
    	      side = 0;
    	    }
    	    else
    	    {
    	      side_dist_y += delta_dist_y;
    	      map_y += step_y;
    	      side = 1;
    	    }//Check if ray has hit a wall
			// printf("Mapa em: %c\n", map->map[map_x][map_y]);
			// printf("map_x: %d\n", map_x);
			// printf("map_y: %d\n", map_y);
			if(map->map[map_x][map_y] == '1')
				hit = 1;
    	}
		// printf("Side é igual a: %d\n", side);
		if(side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
    	else
		  	perp_wall_dist = (side_dist_y - delta_dist_y);
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist); //Calculate height of line to draw on screen
		printf("Altura da linha é: %d\n", line_height);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		printf("Começo da parede: %d\n", draw_start);
    	if(draw_start < 0)
			draw_start = 0;
    	int drawEnd = line_height / 2 + SCREEN_HEIGHT / 2;
    	if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		//choose wall color
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
		int drawStartTemp = draw_start;
		int	count_pixel_square;

		int *rgb = array_to_int("255, 0, 0");
		if (side != 1)
			color = encode_rgb(rgb[0], rgb[1], rgb[2]);
		else
			color = encode_rgb(110, 9, 9);
		while(drawStartTemp < drawEnd)
		{
			count_pixel_square = 0;
			while (count_pixel_square < 32)
			{
				mlx_pixel_put(map->mlx.mlx_ptr, map->mlx.win, (x + count_pixel_square), drawStartTemp, color);  //<<
				count_pixel_square++;
			}
			drawStartTemp++;
		}
		printf("mano que\n");
		x++;
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


/* abrir uma funcao para tratamento do
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


