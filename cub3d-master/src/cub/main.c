/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:11:59 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/17 03:11:42 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// funcao para exitar game

void	file_error(void)
{
	write(2, "Error: Invalid Map\n", 19);
	exit(1);
}

int main(int argc, char **argv)
{
	char	*extension;
	char	*filename;
	t_map	*map;

	if (argc != 2)
		file_error();
	filename = argv[1];
	extension = &filename[ft_strlen(filename) - 4];
	if (ft_strncmp(".cub", extension, 4))
		file_error();
	map = prepare_to_store(filename);
	validate_map(map);
	game_loop(map);
	return (0);
}

/*
./cub3d ./src/maps/map.cub
valgrind --leak-check=full ./cub3d ./src/maps/map.cub
*/