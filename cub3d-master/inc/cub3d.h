/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:15:32 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/13 16:01:22 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define FT_ERROR 1
# define FT_SUCCESS 0
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 440

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../inc/gnl.h"
# include "../inc/libft.h"
# include "../src/mlx/minilibx-linux/mlx.h"

typedef struct s_ray
{
	char	*rays; //orientacao
	char*	pov;
	int		index;
	/* init*/
	double dir_x; //vetor de direcao inicial eixo x
	double dir_y; //vetor de direcao inicial eixo y
	double plane_x; // versao 2d raycaster do plano de camera
	double plane_y;
	// double time; //tempo do quadro atual
	// double old_time; //tempo do frame anterior
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double	pos_x;  //posicao inicial
	double	pos_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		x;
	int	map_x; //posicao atual
	int	map_y;
    int step_x;
    int step_y;
    int hit;
    int side;
	int line_height;
	int draw_start;
	int	color;
	int		draw_end;
	int		draw_start_temp;
	int		count_pixel_square;
	int		*rgb;
}	t_ray;

typedef struct s_background
{
	void	*ptr_img;
	int		*data;
	int		line_size;
	int		bpp;
	int		endian;
}	t_background;

typedef	struct s_rotation
{
	int	right;
	int	left;

}	t_rotation;

typedef struct s_mlx
{
	void			*win;
	void			*mlx_ptr;
}	t_mlx;

typedef	struct s_image
{
	// abaixo: as texturas das paredes e os numeros rgb
	void			*north_wall;
	void			*south_wall;
	void			*west_wall;
	void			*east_wall;
	// void			*floor;
	// void			*ceilling;
}	t_image;

typedef struct s_map //principal
{
	t_mlx			mlx;
	t_image			textures;
	t_background	back;
	t_rotation		rotation;
	t_ray			rays;
	char			**map;
	// char			*north;
	// char			*south;
	// char			*west;
	// char			*east;
	char			*floor;
	char			*ceilling;
	int				monitoring;
	int				height;
	int				width;
	int				fd;
	char			spawing;
}	t_map;

enum e_keycode
{
	/* point of view keys */
	KEY_W				= 119,
	KEY_A				= 97,
	KEY_S				= 115,
	KEY_D				= 100,
	KEY_ESC				= 65307,
	ROTATE_LEFT			= 123,
	ROTATE_RIGHT		= 124,
	X_EVENT_KEY_EXIT	= 17,
	X_EVENT_KEY_PRESS	= 2
};

/* Functions */
void	draw_stripe(t_map *map);
void	check_color(t_map *map);
void	calculate_init_ray(t_map *map);
void	calculate_ray_lenght(t_map *map);
void	calculate_initial_step_x(t_map *map);
void	calculate_initial_step_y(t_map *map);
void	check_distance_height_pixel(t_map *map);
void	check_ray_hit_wall(t_map *map);
char	*dec_to_hexa(int color);
char	*rgb_to_hexa(t_map *map);
void	render_minimap(t_map *map);
void	get_rays(t_map *map);
void	*open_img(t_map *map, char *path);
void	path_img(t_map *map);
void	free_pointers(t_map *map);
int		end_program(t_map *map);
void	color_background(t_map *map, int width, int height);
void	move_player(t_map *map, int x, int y);
void	free_map(t_map *map);
void	*open_img(t_map *map, char *path);
int		event_key(int keycode, t_map *map);
void	path_img(t_map *map);
void	clear_screen(t_map *map);
void	render_scenes(t_map *map);
void	*open_img(t_map *map, char *path);
void	path_image(t_map *map);
void	free_pointers(t_map *map);
int		end_program(t_map *map);
int		minimize_window(t_map *map);
void	render_minimap(t_map *map);
void	get_rays(t_map *map);
void 	game_loop(t_map *map);
void	validate_floor(t_map *map);
void	validate_ceilling(t_map	*map);
void	validate_texture(t_map *map);
//void verif_char(t_map *map);
int		validate_map(t_map *map);
int		measure_width(char	**line, t_map *map);
void	measure_height(char **line, t_map *map);
void	store_map(char **line, t_map *map, char *filename);
t_map	*prepare_to_store(char *filename);
void	file_error(void);
#endif
