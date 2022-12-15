/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:15:32 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/14 22:27:50 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "./get_next_line.h"
# include "./libft.h"
# include "../src/mlx/minilibx-linux/mlx.h"
# include <stdint.h>
# include <sys/time.h>

# define FT_ERROR 1
# define FT_SUCCESS 0
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 800
# define SMALLER_THAN_MAP_SIZE 1
# define TEXTURES_DONE 4
# define RGB_DONE 2
# define INTERNAL_CHAR "0NSWE"
# define GAMER "NSWE"
# define MAP_S 32
# define PI 3.1415926535
# define DR 0.0174533

typedef struct s_col
{
	int	pos_x;
	int	pos_y;
	int	pos_x_add_offset_x;
	int	pos_y_add_offset_y;
	int	pos_y_sub_offset_y;
	int	pos_x_sub_offset_x;
}	t_col;

/* variáveis usadas para mapear */
/* os pixels das texturas que estão sendo pintados */
typedef struct s_3dmap
{
	float	centered_vision;
	float	line_height;
	int		*data_tile;
	float	texture_x;
	float	texture_y_step;
	float	texture_y_off;
	float	texture_y;
}	t_3dmap;

/* ray_x e ray_y = coordenada inicial do raio */
/* pos_x e pos_y = coordenada inicial/atual do jogador */
/* deltax e deltay = valor que o jogador "percorre" a cada */
/* vez que as teclas de movimento são pressionadas */
/* step_x e step_y = comprimento interno da celula em x e em y */
typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	pos_x;
	float	pos_y;
	float	gamer_angle;
	float	deltax;
	float	deltay;
	int		map_x;
	int		map_y;
	float	step_x;
	float	step_y;
	int		*rgb;
	int		depth_of_field;
	float	neg_tan;
	float	neg_inv_tan;
	float	dist_horizontal;
	float	dist_vertical;
	float	dist_final;
	t_col	collision;
}	t_ray;

typedef struct s_background
{
	void	*ptr_img;
	int		*data;
	int		line_size;
	int		bpp;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*win;
	void	*mlx_ptr;
}	t_mlx;

typedef struct s_textures
{
	char			*east_wall;
	char			*west_wall;
	char			*north_wall;
	char			*south_wall;
	int				width;
	int				height;
	t_image			east_tile;
	t_image			west_tile;
	t_image			north_tile;
	t_image			south_tile;
}	t_textures;

typedef struct s_map
{
	t_mlx			mlx;
	t_textures		textures;
	t_image			back;
	t_ray			rays;
	char			**map;
	char			*floor;
	char			*ceilling;
	int				monitoring;
	int				is_squared_map;
	int				height;
	int				width;
	int				fd;
	char			spawing;
}	t_map;

/* point of view keys */
enum e_keycode
{
	KEY_W	= 119,
	KEY_A	= 97,
	KEY_S	= 115,
	KEY_D	= 100,
	KEY_ESC	= 65307,
	ROTATE_LEFT	= 0xff51,
	ROTATE_RIGHT	= 0xff53,
	X_EVENT_KEY_EXIT	= 17,
	X_EVENT_KEY_PRESS	= 2
};

/* Abaixo: funções da parte GRÁFICA (segunda parte: depois do */
/* armazenamento e validação do conteúdo do arquivo) */
/* Funções de apoio: (devolve um int rgb e free_map() */
/* libera tudo antes de exitar)*/
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	free_map(t_map *map);

void	draw_wall_strip(t_3dmap *scene, t_map *map, int rays_counter);
void	define_walltexture(t_3dmap *scene, t_ray *rays, t_textures *textures);
void	draw_3d(t_ray *ray, float dist_final, int rays_counter, t_map *map);
void	fix_fish_eye(t_ray *rays);
int		check_smaller_ray(t_ray *rays, float *horiz_coord, float *vert_coord);
float	measure_ray_dist(float beginX, float beginY, float endX, float endY);
int		is_wall_hit(t_ray *rays, int map_width, int map_height, char **map);
void	check_axis(int *axis_depth, t_map *map, float **ray_axis, char *axis);
void	find_hit(t_map *map, float *ray_end_x, float *ray_end_y, char *axis);
int		check_vertical_hit(t_map *map, float *vx, float *vy);
int		check_horizontal_hit(t_map *map, float *hx, float *hy);
void	init_hit_data(t_map *map, float *rayX, float *rayY, float *ray_dist);
void	keep_angle_limits(float *ray_angle);
void	move_gamer(char **map, t_ray *rays, char *movement);
void	rotate_gamer(t_ray *rays, char *direction);
void	check_collision(t_ray *rays);

int		event_key(int keycode, t_map *map);
void	cast_rays(t_map *map);
void	color_background(t_map *map);

int		end_program(t_map *map);
int		minimize_window(t_map *map);

int		check_resolution(t_map *map);
void	init_gamer_angle(char spawning, float *gamer_angle);
int		open_texture(t_mlx *mlx, t_image *tile, int *coord, char *path);
int		textures_init(t_textures *textures, t_mlx *mlx);
int		rays_struct_init(t_map *map);
void	game_loop(t_map *map);

/* Funções abaixo: para armazenamento e validação do conteúdo do arquivo */
/* do mapa -> caminhos das texturas, codigos rgb e conteúdo do mapa */

int		ft_is_space(char letter);
int		is_eroded_internal_wall(char **map_line, int char_counter);
int		check_is_closed(char **map_line, int char_counter);
void	store_player_info(t_map *map, char spawn, int row, int column);
int		is_single_gamer(t_map *map, char spawn, int row, int column);
int		is_valid_char(char map_char);
int		is_char_border_or_empty_line(char **map_line, int char_counter);
int		check_map_interior(t_map *map, char **map_line, int row);
int		is_wall(char *map_line, int map_height);
int		is_first_last_row(int counter_row, int height);
int		is_map_open(t_map *map);
void	validate_texture(t_map *map);
void	map_error(t_map *map);
int		validate_rgb(char *rgb_value);
int		validate_map(t_map *map);

void	check_which_rgb(char *line, char **floor, char **ceilling, t_map *map);
void	save_textures_rgb(char *line, t_map *map);
void	free_textures(t_map *map);
void	invalid_rgb(char *line, char *rgb_to_free, t_map *map);
int		is_empty_line(char *line);
int		is_rgb_color(char *line);
void	invalid_texture(char *line, t_map *map, char *error_message);
int		is_texture_path(char *line);
int		store_file_content(char **line, t_map *map, char *filename);

int		count_height_width(char *line, t_map *map);
void	check_textures_rgb(char *line, int *monitoring);
int		measure_height(char **line, t_map *map);
t_map	*prepare_to_store(char *filename);

void	file_error(char *error_message, int error_code);
void	free_matrix(char **split_values);
#endif
