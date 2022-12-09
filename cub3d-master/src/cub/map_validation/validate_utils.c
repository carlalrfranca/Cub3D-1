/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:26:27 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/08 19:52:04 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_single_gamer(t_map *map, char spawn, int row, int column)
{
	if(!map->spawing)
	{
		store_player_info(map, spawn, row, column);
		return(1);
	}
	return(0);
}

int	ft_is_space(char letter)
{
	if(letter == ' ')
		return(1);
	return(0);
}

int	is_valid_char(char map_char)
{
	if(!ft_strchr("10 NSEW", map_char))
		return(0);
	return(1);
}

void	store_player_info(t_map *map, char spawn, int row, int column)
{
	map->spawing = spawn;
	map->rays.pos_x = column * map_s;
	map->rays.pos_y = row * map_s;
	map->map[row][column] = '0';
}

int is_first_last_row(int counter_row, int height)
{
    if((counter_row == 0 || counter_row == (height - 1)))
        return (1);
    return(0);
}
