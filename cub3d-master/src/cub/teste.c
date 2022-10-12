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
