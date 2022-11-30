/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:15:32 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/30 17:03:35 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define FT_ERROR 1
# define FT_SUCCESS 0
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

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
# include <stdint.h>
# include <sys/time.h>

// macros para monitorar o tipo de conteudo que foi extraído do mapa
#define TEXTURES_DONE 4
#define	RGB_DONE 2
#define INTERNAL_CHAR "0NSWE"
#define GAMER "NSWE"
#define map_s 32 //map cube size
#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI/2
#define DR 0.0174533 //um degrau em radiano

typedef struct s_col
{
    int col_pos_x;
	int col_pos_y;
	int	col_pos_x_add_offset_x;
	int	col_pos_y_add_offset_y;
	int col_pos_y_sub_offset_y;
	int col_pos_x_sub_offset_x;
} t_col;

typedef struct s_ray
{
	char	*rays; //orientacao
	int	index;
	double	dir_x; //vetor de direcao inicial eixo x
	double	dir_y; //vetor de direcao inicial eixo y
	float 	ray_x; //posiciao inicial do raio rx e ry
	float 	ray_y;
	float	pos_x; //px
	float	pos_y; //py
	float	gamer_angle; //pa
	float	deltax;//pdx; //delta x
	float 	deltay;//pdy; //delta y
	int	x;
	int	map_x; //posicao atual
	int	map_y;
	float 	step_x; //comprimento inicial interno da celula xo
    	float 	step_y; //comprimento final interno da celula yo
	int	*rgb;
	int	depth_of_field; //dof
	float	ray_angle;
	float 	neg_tan; //ntan negativo da tangente
	float 	neg_inv_tan; //atan negativo do invers
	float 	dist_horizontal; //dish;
	float 	dist_vertical; //disv;
	float	dist_final;
        t_col   collision;
}	t_ray;

typedef struct s_background
{
	void	*ptr_img; //ptr_map
	int	*data;
	int	line_size;
	int	bpp;
	int	endian;
}	t_background;

typedef struct s_mlx
{
	void	*win;
	void	*mlx_ptr;
}	t_mlx;

typedef	struct s_image
{// abaixo: as texturas das paredes e os numeros rgb
	char	*east_wall;//strings dos caminhos
	char	*west_wall;
	char	*north_wall;
	char	*south_wall;
	int	width;
	int 	height;
	t_background	east_tile;
	t_background	west_tile;
	t_background	north_tile;
	t_background	south_tile;
}	t_image;

typedef struct s_map //principal
{
	t_mlx	mlx;
	t_image	textures;
	t_background	back;
	t_background	map2d;
	t_background	gamer;
	t_ray	rays;
	char	**map;
	char	*floor;
	char	*ceilling;
	int	monitoring;
	int	height; //map_y -altura
	int	width; //map_x -largura
	int	fd;
	char	spawing;
}	t_map;

enum e_keycode
{
	/* point of view keys */
	KEY_W	= 119,
	KEY_A	= 97,
	KEY_S	= 115,
	KEY_D	= 100,
	KEY_ESC	= 65307,
	ROTATE_LEFT	= 123,
	ROTATE_RIGHT	= 124,
	X_EVENT_KEY_EXIT	= 17,
	X_EVENT_KEY_PRESS	= 2
};

int     check_smaller_ray(t_ray *rays, float *horiz_position, float *vert_position);
void    fix_fish_eye(t_ray *rays);
void	keep_angle_limits(float *ray_angle);
void    draw_3d(t_ray *ray, float dist_final, int rays_counter, t_map *map);
void    check_axis(int *axis_depth, t_map *map, float **ray_axis, char *axis);
void    init_ray_projection_values(t_map *map, float *rayX, float *rayY, float *ray_dist);
void    search_hit_point(t_map *map, float *ray_end_x, float *ray_end_y, char *axis);
int     check_vertical_hit(t_map *map, float *vx, float *vy);
int     check_horizontal_hit(t_map *map, float *hx, float *hy);
void    rotate_gamer(t_ray *rays, char *direction);
void    move_gamer(char **map, t_ray *rays, char *movement);
void    open_texture(t_mlx *mlx, t_background *tile, int *coord, char *path);
void	textures_init(t_image *textures, t_mlx *mlx);
float	measure_ray_dist(float beginX, float beginY, float endX, float endY);
int	minimize_window(t_map *map);
int	end_program(t_map *map);
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int     draw_ray_2d(t_ray *rays, t_background *map2d, int map_width, int color);
void	cast_rays(t_map *map);
void	paint_gamer(t_map *map);
void	paint_map(t_map *map);
int	event_key(int keycode, t_map *map);
void	move_player(t_map *map, int x, int y);
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
void	move_player(t_map *map, int x, int y);
void	free_map(t_map *map);
void	*open_img(t_map *map, char *path);
int	event_key(int keycode, t_map *map);
void	path_img(t_map *map);
void	clear_screen(t_map *map);
void	color_background(t_map *map);
void	*open_img(t_map *map, char *path);
void	path_image(t_map *map);
void	free_pointers(t_map *map);
int	minimize_window(t_map *map);
void	render_minimap(t_map *map);
void	get_rays(t_map *map);
void	rays_struct_init(t_map *map);
void 	game_loop(t_map *map);
int	is_wall(char *map_line, int map_height);
int	is_valid_char(char map_char);
void	store_player_info(t_map *map, char spawn, int row, int column);
int	is_single_gamer(t_map *map, char spawn, int row, int column);
int	ft_is_space(char letter);
int	check_is_closed(char **map_line, int char_counter);
int	check_map_interior(t_map *map, char **map_line, int row);
int	is_map_open(t_map *map);
void	validate_floor(t_map *map);
void	validate_ceilling(t_map	*map);
void	validate_texture(t_map *map);
void	map_error(t_map *map);
int	validate_map(t_map *map);
int	measure_width(char	**line, t_map *map);
void	measure_height(char **line, t_map *map);
void	store_map(char **line, t_map *map, char *filename);
t_map	*prepare_to_store(char *filename);
void	file_error(void);
void	free_matrix(char **split_values);
#endif
