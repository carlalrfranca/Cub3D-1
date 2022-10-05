/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:15:32 by cleticia          #+#    #+#             */
/*   Updated: 2022/10/05 16:43:42 by cleticia         ###   ########.fr       */
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
# include "../inc/gnl.h"
# include "../inc/libft.h"
# include "../src/mlx/minilibx-linux/mlx.h"

# define FT_ERROR 1
# define FT_SUCCESS 0
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 440

typedef struct s_ray
{
	char	*rays; //orientacao
	int		index;
	char*	pov;
}	t_ray;

typedef struct s_background
{
	void	*ptr_img;
	int		*data;
	int		line_size;
	int		bpp;
	int		endian;
}	t_background;

typedef struct s_mlx
{
	void			*win;
	void			*mlx_ptr;
}	t_mlx;

typedef	struct s_image
{
	void			*north_wall;
	void			*south_wall;
	void			*west_wall;
	void			*east_wall;
	void			*floor;
	void			*ceilling;
}	t_image;

typedef struct s_map //principal
{
	t_mlx			mlx;
	t_image			img;
	t_background	back;
	t_ray			rays;
	char			**map;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceilling;
	int				monitoring;
	int				height;
	int				width;
	int				fd;
	char			spawing;
	int				pos_x;
	int				pos_y;
}	t_map;

enum e_keycode
{
	/* point of view keys */
	KEY_W				= 119,
	KEY_A				= 97,
	KEY_S				= 115,
	KEY_D				= 100,
	KEY_ESC				= 65307,
	X_EVENT_KEY_EXIT	= 17,
	X_EVENT_KEY_PRESS	= 2
};

/* Functions */
char	*dec_to_hexa(int color);
char	*rgb_to_hexa(t_map *map);
void	render_minimap(t_map *map);
void	get_rays(t_map *map);
void	*open_img(t_map *map, char *path);
void	path_img(t_map *map);
void	free_pointers(t_map *map);
int	end_program(t_map *map);
void	color_background(t_map *map, int width, int height);
void	move_player(t_map *map, int x, int y);
void	free_map(t_map *map);
void	*open_img(t_map *map, char *path);
int event_key(int keycode, t_map *map);
void	path_img(t_map *map);
void	clear_screen(t_map *map);
void	render_scenes(t_map *map);
void	*open_img(t_map *map, char *path);
void	path_image(t_map *map);
void	free_pointers(t_map *map);
int	end_program(t_map *map);
int	minimize_window(t_map *map);
void	render_minimap(t_map *map);
void	get_rays(t_map *map);
void game_loop(t_map *map);
void	validate_floor(t_map *map);
void	validate_ceilling(t_map	*map);
void	validate_texture(t_map *map);
//void verif_char(t_map *map);
int	validate_map(t_map *map);
int	measure_width(char	**line, t_map *map);
void	measure_height(char **line, t_map *map);
void	store_map(char **line, t_map *map, char *filename);
t_map	*prepare_to_store(char *filename);
void	file_error(void);
#endif
