/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:11:59 by cleticia          #+#    #+#             */
/*   Updated: 2022/09/29 09:20:23 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// funcao para exitar game

void	file_error(void)
{
	write(2, "Error: Invalid Map\n", 19);
	exit(1);
}
/*
	verifica numero de argumentos
	se for != 2 ou se a extensão for != .cub
	segue para funcnao de erro e exita
	se nao starta a funcao para armazenar mapa
	depois starta a funcao para validar mapa se tudo ok retorna
	para startar o loop princimake repal onde inicia  a minilibX e a renderizacao
*/

int main(int argc, char **argv)
{
	char	*extension;
	char	*filename;
	t_map	*map;

	filename = argv[1];
	extension = &filename[ft_strlen(filename) - 4];
	if (argc != 2 || ft_strncmp(".cub", extension, 4))
		file_error();
	map = prepare_to_store(filename);
	validate_map(map);
	game_loop(map);
	return (0);
}

/*
ou dessa forma
int main(int argc, char **argv)
{
	char	*extension;
	char	*filename;

	filename = argv[1];
	printf("*** cheguei aqui na main 1 ***\n");
	printf("argc: %d\n", argc);
	extension = ft_strrchr(filename, '.');
	if (argc != 2 || ft_strncmp(extension, ".cub", 4) != 0)
		filename_error();
	prepare_to_store(filename);
	//validate_map();
	//game_loop();
	return (0);
}
*/

/*

valgrind --leak-check=full ./cub3d ./src/maps/map.cub
valgrind --leak-check=full ./cub3d ./src/maps/map.cub

*/
