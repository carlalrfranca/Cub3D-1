/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:25 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/05 16:20:38 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
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

char	*dec_to_hexa(int color)
{
	char	*hexa_dec;
	char	*hex_code;
	int		cnt_digit;
	int		index;
	int		temp;
	int		number;

	hex_code = "";
	cnt_digit = 0;
	index = 0;
	temp = 0;
	number = color;
	while (number)
	{
		number /= 10;
		cnt_digit++;	
	}
	while (color != 0)
	{
		temp = color % 16;
		if (temp < 10)
		{
			hexa_dec[index] = temp + 48; //digito 0
			index++;
		}
		else
		{
			hexa_dec[index] = temp + 55;
			index++;
		}
		color = (color / 16);
	}
	if (index == 2)
		hex_code = ft_strjoin(hex_code, hexa_dec);
	else if (index == 1)
	{
		hex_code = "0";
		hex_code = ft_strjoin(hex_code, hexa_dec);//hex_code = hex_code + hexa_dec[0];
	}
	else if (index == 0)
	hex_code = "00";
	return(hex_code);
}

char	*rgb_to_hexa(t_map *map)
{
	int		red;
	int		green;
	int		blue;
	int		index;
	char	**rgb;
	char	*hex_code;
	char	*rgb_value;

	red = 0;
	green = 0;
	blue = 0;
	index = -1;
	rgb = ft_split(rgb_value, ',');
	if (rgb_value[index])
	{
		red = ft_atoi(rgb[0]);
		green = ft_atoi(rgb[1]);
		blue = ft_atoi(rgb[2]);
	}
	hex_code = 0;
	hex_code += *dec_to_hexa(red);
    hex_code += *dec_to_hexa(green);
    hex_code += *dec_to_hexa(blue);
	return(hex_code);
}

void	render_minimap(t_map *map)
{

	map->north = 0;
	printf("na render mini map");
}

void	get_rays(t_map *map)
{
	double dir_x; //vetor de direcao inicial
	double dir_y;
	double plane_x; // versao 2d raycaster do plano de camera
	double plane_y;
	double time; //tempo do quadro atual
	double old_time; //tempo do frame anterior
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int		x;
	int	map_x; //posicao atual na celula
	int	map_y;
	int	pos_x; //posicao
	int	pos_y;
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

	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	time = 0;
	old_time =0;
	x = 0;
	hit = 0;
	map_x = pos_x;
	map_y = pos_y;
	delta_dist_y = ray_dir_y;
	while( x < SCREEN_WIDTH) //calcula a posição e direção do raio
	{
		camera_x = (2 * x) / (SCREEN_HEIGHT - 1); //coordenada no espaço da camera
		ray_dir_x = dir_y + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;
		if(ray_dir_x == 0)
			delta_dist_x = 1e30;
		else 
			delta_dist_x = (int) abs(1 / (int)ray_dir_x);
		if(ray_dir_y == 0)
			delta_dist_y = 1e30;
		else 
			delta_dist_y = (int) abs(1 / (int)ray_dir_y);
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
			if(map->map[map_x][map_y] > 0) hit = 1;
    	}
		if(side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
    	else
		  	perp_wall_dist = (side_dist_y - delta_dist_y);
		line_height = (int)(h / perp_wall_dist); //Calculate height of line to draw on screen
		draw_start = -line_height / 2 + h / 2;
    	  if(draw_start < 0) draw_start = 0;
    	  int drawEnd = line_height / 2 + h / 2;
    	  if(drawEnd >= h) drawEnd = h - 1;

		//choose wall color
		if(map->map[map_x][map_y] == 1)
		{
			// vermelho --> 255, 0, 0 --> 0xFF0000
		}
		//dar aos lados x e y diferentes brilhos
		if (side == 1)
		{
			// divide o vermelho por 2 (125, 0, 0)
		}
		// 'h' deve ser a macro SCREEN_HEIGHT (pq é em pixels)
		//cria uma imagem (funcao minilibx) pra poder "pintar"
		// usando data (e outros ponteiros) e, ao final, usar
		// a funcao put_image da minilibx
		// essa parte toda corresponde à linha 196 (verLine()) do tutorial
		//pra desenhar os pixels de toda a coluna, vai ter que ter um while\
		// para do draw_start ao drawEnd?
		int drawStartTemp = draw_start;
		int	count_pixel_square;
		while(drawStartTemp < drawEnd)
		{
			count_pixel_square = 0;
			while (count_pixel_square < 32)
			{
				mlx_pixel_put(map->mlx.mlx_ptr, map->mlx.win, (x * 32 + count_pixel_square), drawStartTemp, #color);
				count_pixel_square++;
			}
			drawStartTemp++;
		}
	}
	//timing pra input e contador de FPS
	old_time = time;
	struct timeval current_time;
  	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec;
	double frameTime = (time - old_time) / 1000.0;

	// modificadores de velocidades
	double moveSpeed = frameTime * 5.0;
	double rotSpeed = frameTime * 3.0;

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
	int		height;
	int		width;

	height = 0;
	width = 0;
	ptr = mlx_xpm_file_to_image(map->mlx.mlx_ptr, path, &width, &height);
	if (!height || !width)
	{
		write(2, "ERROR\n", 6);
		write(2, "Without image\n", 14);
		exit(1);
	}
	return (ptr);
}

void	path_img(t_map *map)
{
	map->img.north_wall = open_img(map, "../img/north_texture.png");
	map->img.south_wall = open_img(map, "../img/south_texture.png");
	map->img.west_wall = open_img(map, "../img/west_texture.png");
	map->img.east_wall = open_img(map, "../img/east_texture.png");		
}

void	free_pointers(t_map *map)
{
	free(map->mlx.mlx_ptr);
	free_map(map);
}

int	end_program(t_map *map)
{
	if (map->north != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.north_wall);
	if (map->south != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.south_wall);
	if (map->west != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.west_wall);
	if (map->east != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.east_wall);
	mlx_destroy_image(map->mlx.mlx_ptr, map->mlx.win);
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
	void	*img_ptr;
   	int		*data;
    int		size_l;
    int		bpp;
    int		endian;
   
    int count_h = -1;
    int count_w;
	img_ptr = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);

    data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_l, &endian);
    while (++count_h < SCREEN_HEIGHT)
    {
        count_w = -1;
        while (++count_w < SCREEN_WIDTH)
        {
            if (count_h < (SCREEN_HEIGHT/2))
                data[count_h * SCREEN_WIDTH + count_w] = 0xFFFFFF;
            else
                data[count_h * SCREEN_WIDTH + count_w] = 0;
        }
    }
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, img_ptr, 0, 0);
}

int	minimize_window(t_map *map)
{
	mlx_destroy_image(map->mlx.mlx_ptr, map->mlx.win);
	render_scenes(map);//funcao diferente -calculo , raios e 3d* *****
	return (0);
}

void	game_loop(t_map *map)
{
	int	x;
	int	y;

	x = map->width * 64;
	y = map->height * 64;
	map->mlx.mlx_ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, x, y, "cub3d");
	while(map->mlx.win)
	{
		path_image(map);//corrigir
		clear_screen(map);
		render_scenes(map);//corrigir
		mlx_hook(map->mlx.win, X_EVENT_KEY_PRESS, 1 << 0, event_key, map);
		get_rays(map);
		mlx_expose_hook(map->mlx.win, minimize_window, &map);
		mlx_hook(map->mlx.win, X_EVENT_KEY_EXIT, 1 << 0, end_program, map);
		mlx_loop(map->mlx.mlx_ptr);
	}
}


