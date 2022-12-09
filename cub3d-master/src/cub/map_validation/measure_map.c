/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:07:50 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/09 17:23:58 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	check_textures_rgb(char *line, int *monitoring)
{
	static int	texture;
	static int	rgb;

	if (ft_strchr(line, '.'))
	{
		texture++;
		if (texture == TEXTURES_DONE)
			(*monitoring) += 4;
	}
	else if (ft_strchr(line, ','))
	{
		rgb++;
		if (rgb == RGB_DONE)
			(*monitoring) += 2;
	}
}

/*
** a gente pode usar essa função pra monitor se o tamanho das linhas é
** diferente em relação uma à outra:
** caso o map->width seja != 0 (se não tiver essa guarda, ele pode
** acabar entendendo que as linhas do mapa tem largura diferente, sendo
** que é só a PRIMEIRA VEZ que ele tá guardando (no inicio, map->width = 0))
** então.. caso map->width != 0 e é também != size que acabou de ser tirado,
** então significa que as linhas tem tamanhos diferentes.
** Senão, por enquanto está sendo um mapa quadrado.
** Mas o ponto é:
** usa isso pra monitorar e RETORNA ESSE valor (verdadeiro pra se
** o mapa é quadrado, falso pra sinalizar que não é - e precisa ter suas
** linhas preenchidas com espaço).
** Quando voltar pra measure_height(), caso o retorno da count_height_width
** seja a de que o mapa NÃO É QUADRADO, na hora de ARMAZENAR O MAPA, sempre
** comparar o tamanho de cada linha com a da width total,
** e aquelas que forem menores, serem PREENCHIDAS/AJUSTADAS antes de
** serem gravadas na matriz do mapa.
** provavelmente vai ter que inserir essa variável (is_map_squared)
** na struct map pra poder repassar
** Error 505 -> WRONG FORMATTING
*/
int	count_height_width(char *line, t_map *map)
{
	int		size;

	if (map->monitoring != 6)
	{
		free(line);
		return (505);
	}
	map->height++;
	size = ft_strlen(line);
	if (map->width != 0 && size != map->width)
		map->is_squared_map = 0;
	if (size > map->width)
		map->width = size;
	return (0);
}

/*
** measure_height() vai tirar a altura da matriz do mapa (que servirá para o minimapa e
** para projetar o mapa 3d tambem).
*/
int	measure_height(char **line, t_map *map)
{
	int		ret;

	ret = 1;
	while (ret)
	{
		if (line && (*line))
			free(*line);
		ret = get_next_line(map->fd, line);
		if (ret == 0 && map->height == 0 && map->monitoring == 0)
			return (505);
		if (ft_strchr(*line, '.') || ft_strchr(*line, ','))
			check_textures_rgb(*line, &map->monitoring);
		else if (is_empty_line(*line) && map->height == 0)
			continue ;
		else if (count_height_width(*line, map) == 505)
			return (505);
	}
	if (*line)
		free(*line);
	if (map->height == 0)
	{
		close(map->fd);
		return (505);
	}
	return (0);
}
