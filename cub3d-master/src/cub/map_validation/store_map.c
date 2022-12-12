/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:10:59 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/09 17:35:14 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* ------------------------------------ abaixo: */
/* ------- funções de suporte para a save_map() */
/* - int check_line_length(char *line, int map_width) */
/*	---> returns the difference to fill. If returns 0,*/
/* there's no difference to fill */
/* - void fill_difference(char **line) */
static void	fill_difference(char **line, int map_width)
{
	int		difference_to_fill;
	char	*only_spaces;
	char	*filled_line;

	difference_to_fill = map_width - ft_strlen(*line);
	only_spaces = malloc(sizeof(char) * (difference_to_fill + 1));
	only_spaces[difference_to_fill] = '\0';
	ft_memset(only_spaces, ' ', difference_to_fill);
	filled_line = ft_strjoin((*line), only_spaces);
	free(only_spaces);
	free((*line));
	(*line) = filled_line;
}

static int	check_line_length(char *line, int map_width)
{
	size_t	length;

	length = ft_strlen(line);
	if ((int)length != map_width)
		return (SMALLER_THAN_MAP_SIZE);
	return (0);
}

/* save_map() armazena o conteúdo do mapa na matriz da estrutura principal*/
/* antes disso, porém, verifica se os caminhos das texturas e os */
/* códigos rgb já estão armazenados na estrutura (ou seja, já */
/* "passamos" por eles no arquivo).*/
/* Caso não, ele retorna erro e exita, porque faz parte das regras */
/* que o mapa deva ser O ULTIMO conteudo do arquivo (e tambem há */
/* a possibilidade de nem ter */
/* caminhos de texturas e/ou codigos rgb). */
/**/
/* Se a variavel is_squared_map for == 0, significa que há linhas */
/* diferentes, daí vamos para um fluxo que vai receber a linha atual, */
/* comparar sua largura com a width do mapa e, se for uma das linhas */
/* menores, vai preenche-la com espaços vazios pela */
/* quantidade da diferença e armazená-la. */
/* Usa como apoio: */
/* - is_map_square() */
/* - check_line_length() */
/* - fill_difference() */
static void	save_map(t_map *map, int *content, char **line)
{
	if ((*content) == 0 && (!map->textures.east_wall || !map->textures.west_wall
			|| !map->textures.south_wall || !map->textures.north_wall
			|| !map->ceilling || !map->floor))
		invalid_texture((*line), map, "Error\nTexture or RGB error.");
	map->monitoring = 0;
	if (map->is_squared_map == 0)
	{
		if (check_line_length(*line, map->width) == SMALLER_THAN_MAP_SIZE)
			fill_difference(line, map->width);
	}
	map->map[*content] = ft_strdup(*line);
	(*content)++;
}

/*
** store_file_content() irá abrir o arquivo onde estão os caminhos para
** as texturas, os códigos rgb e o mapa e irá percorrer esse conteúdo,
** separando-os e armazenando-os em variáveis na estrutura principal.
** Usa para isso as funções de apoio:
** - save_textures_rgb()
** - save_map()
*/
int	store_file_content(char **line, t_map *map, char *filename)
{
	int		ret;
	int		content;

	ret = 1;
	content = 0;
	map->fd = open(filename, O_RDONLY);
	while (ret)
	{
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0)
			return (303);
		if (ft_strlen((*line)) != 0
			&& ((is_texture_path(*line)) || is_rgb_color(*line)))
			save_textures_rgb((*line), map);
		else if (is_empty_line(*line) && (map->monitoring == 6))
		{
			free(*line);
			continue ;
		}
		else
			save_map(map, &content, line);
		free(*line);
	}
	return (0);
}
