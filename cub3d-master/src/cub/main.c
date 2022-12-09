/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:11:59 by cleticia          #+#    #+#             */
/*   Updated: 2022/12/09 18:29:00 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	file_error(char *error_message, int error_code)
{
	ft_putendl_fd(error_message, 2);
	exit(error_code);
}

int	main(int argc, char **argv)
{
	char	*extension;
	char	*filename;
	t_map	*map;

	if (argc != 2)
		file_error("Error\nInvalid number of arguments", 1);
	filename = argv[1];
	extension = &filename[ft_strlen(filename) - 4];
	if (ft_strncmp(".cub", extension, 4))
		file_error("Error\nWrong file extension.", 1);
	map = prepare_to_store(filename);
	validate_map(map);
	game_loop(map);
	return (0);
}
