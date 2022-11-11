/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:36 by cleticia          #+#    #+#             */
/*   Updated: 2022/11/11 00:22:21 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	free_map(t_map *map)
{
	int	index;

	index = -1;
	while (++index < map->height)
		free(map->map[index]);
	free(map->map);
}

void	map_error(t_map *map)
{
	free_map(map);
	write(2, "Error : Invalid Map\n", 20);
	exit(1);
}

int	is_two_commas(char *rgb_value)
{
	int	index;
	int	total_commas;

	index = 0;
	total_commas = 0;
	while (rgb_value[index])
	{
		if (rgb_value[index] == ',')
			total_commas++;
		index++;
	}
	if (total_commas != 2)
		return (0);
	return (1);
}

void	validate_rgb(char *rgb_value)
{
	char **split_values;
	int	rgb;
	int	i;
	int	j;

	i = -1;
	rgb = 0;
	if (!is_two_commas(rgb_value))
		file_error();
	split_values = ft_split(rgb_value, ',');
	while(split_values[++i])
	{
		j = -1;
		while (split_values[i][++j])
		{
			if(ft_isdigit(split_values[i][j]) == -1)
				file_error();
		}
		rgb = ft_atoi(split_values[i]);		
		if (rgb < 0 || rgb > 255)
			file_error();
	}
	if(i != 3)
		file_error();
}

void	validate_texture(t_map *map)
{
	if(map->textures.north_wall == 0 || map->textures.south_wall == 0
		|| map->textures.west_wall == 0 || map->textures.east_wall == 0)
		map_error(map);
}

void verif_char(t_map *map)
{
	char	letter;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			letter = map->map[i][j];
			if (letter != '0' && letter != ' ' && letter != '1'
				&& letter != 'N' && letter != 'S' &&letter != 'E' && letter != 'W') //substituir por ft_strncmp()
				map_error(map);
			if (letter == 'S' || letter == 'N' || letter == 'E'
				|| letter == 'W')
			{
				map->spawing = letter;
				map->rays.pos_x = j;
				map->rays.pos_y = i;
			}
			j++;
		}
		i++;
	}
}



// int validate_row(char **map, int pos_x, int pos_y, char to_skip)
// {
// 	int x;

// 	x = pos_x;
// 	if (x > 0 && map[pos_y][x - 1] != '1')
// 		return (-30);
// 	while (map[pos_y][x] && map[pos_y][x] == to_skip)
// 		x++;
// 	if (map[pos_y][pos_x] == ' ' && map[pos_y][x] == '\0' && map[pos_y][pos_x - 1] == '1')
// 	{
// 		return (x - 1); //nesse caso, é o caracter nulo e vai precisar compensar pra la fora
// 		// nao acessarmos espaço indevido na string
// 	}
// 	else if (map[pos_y][x] != '1')
// 	{
// 		printf("%d e %d\n", pos_y, x); //ta dando erro pq ta pegando o caracter do gamer.. podemos
// 		// salvar sua posicao em x e y e substitui-lo por 0 pra nao ter problema?
// 		return (-30);
// 	}
// 	else
// 		return (x);
// }

// int validate_columns(t_map *map)
// {
// 	int x_axis;
// 	int y_axis;
// 	int	skip_spaces;

// 	// a ideia é percorrer verticalmente (ou seja, o y A CADA ITERAÇÃO)
// 	y_axis = 0;
// 	x_axis = 0;
// 	while (x_axis < map->width)
// 	{
// 		y_axis = 0;
// 		while (y_axis < map->height)
// 		{
// 			if (map->map[y_axis][x_axis] == ' ')
// 			{

// 			}
// 			else if (map->map[y_axis][x_axis] == '0')
// 			{
				
// 			}
// 			// if(map->map[y_axis][x_axis] == ' ')
// 			// {
// 			// 	// rodar até encontrar '1' (e atualizar a pos_x), senao dá erro
// 			// 	skip_spaces = validate_row(map->map, x_axis, y_axis, ' ');
// 			// 	if (skip_spaces < 0)
// 			// 		return (skip_spaces);
// 			// 	else
// 			// 		x_axis += (skip_spaces - x_axis); //atualizar a posicao em x
// 			// }
// 			// else if (map->map[y_axis][x_axis] == '0')
// 			// {
// 			// 	// printf("Encontrou zero: %d e %d\n", y_axis, x_axis);
// 			// 	skip_spaces = validate_row(map->map, x_axis, y_axis, '0');
// 			// 	if (skip_spaces < 0)
// 			// 		return (skip_spaces);
// 			// 	else
// 			// 		x_axis += (skip_spaces - x_axis);
// 			// }
// 			y_axis++;
// 		}
// 		x_axis++;
// 	}
// }


// acho que em vem da função acima, a gente pode criar uma função para verificar
// que o caracter enviado é aceitável
// e daí dentro do loop verificar cada char (substitui a verify_char)


// loop principal pra verificar o mapa:
/*
	1)função recebe o mapa
	2)loop sobre cada STRING do mapa
	3)verifica que a primeira string seja parede ('1's ou espaços vazios)
	4)nas demais (até ANTES DA ÚLTIMA), enviar para uma função
		que vai verificar se o caracter é valido (1 0NSEW) && se é caracter interno (0NSWE) - tirando parede e espaço vazio
		- se for, verifica AO REDOR dele, e se tiver espaço vazio/nulo, RETORNA ERRO (e dá mapa inválido),
		senão, prossegue.
	5)Dentro do loop, terá uma condição pra se for a ÚLTIMA LINHA (i == 0 || i == (map->height - 1))
	  que será enviada para a mesma função que recebeu a primeira linha e verifica se é parede ('1's ou espaços vazios)
	
	-----------------------
	OBS: Precisamos GARANTIR que haja apenas UM PERSONAGEM, se houver mais, DÁ ERRO! (macro GAMER[NSEW]?)

	OBS2: A gente também tem que invalidar o mapa caso ele tenha LINHAS VAZIAS NO MEIO..
*/

// vale funções daqui pra baixo + free_map(), map_error(), validate_rgb(), validate_texture(), is_two_commas()

int	is_wall(char *map_line)
{
	int	char_counter;

	char_counter = 0;
	while(map_line[char_counter])
	{
		// se o caracter não for nem 1 nem espaço vazio retorna zero (erro)...
		if(!ft_strchr("1 ", map_line[char_counter]))
			return (0);
		char_counter++;
	}
	return (1);
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
	map->rays.pos_x = column;
	map->rays.pos_y = row;
}

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

int	check_is_closed(char **map_line, int char_counter)
{
	// pra verificar as linhas anterior e posteriores, precisa acessar
	// o ENDEREÇO em (-1) e (+1) / e (0).. por isso precisa
	// passar a linha por ENDEREÇO/PONTEIRO. Se for por valor, será
	// apenas uma CÓPIA do valor da string EM OUTRO ESPAÇO DE MEMORIA,
	// e NAO DARÁ PRA ACESSAR AS LINHAS ANTERIORES/POSTERIORES DO MAPA
	
	// teste pra ver se imprime a linha anterior, a anterior e a posterior (linhas do mapa):
	/*
		printf("anterior: %s\natual: %s\nposterior: %s\n", map_line[0], map_line[-1], map_line[+1]);
	*/

	if(ft_is_space(map_line[0][char_counter - 1]) || !map_line[0][char_counter - 1])
		return(0);
	if(ft_is_space(map_line[0][char_counter + 1]) || !map_line[0][char_counter + 1])
		return(0);
	if(ft_is_space(map_line[-1][char_counter]) || !map_line[-1][char_counter])
		return(0);
	if(ft_is_space(map_line[-1][char_counter - 1]) || !map_line[-1][char_counter - 1])
		return(0);
	if(ft_is_space(map_line[-1][char_counter + 1]) || !map_line[-1][char_counter + 1])
		return(0);
	if(ft_is_space(map_line[1][char_counter]) || !map_line[1][char_counter])
		return(0);
	if(ft_is_space(map_line[1][char_counter - 1]) || !map_line[1][char_counter - 1])
		return(0);
	if(ft_is_space(map_line[1][char_counter + 1]) || !map_line[1][char_counter + 1])
		return(0);
	return(1);
}

int	check_map_interior(t_map *map, char **map_line, int row)
{
	int	char_counter;

	char_counter = 0;
	// aqui verificaremos apenas se tem caracteres validos (o que inclui espaço e 1..)
	// MAS TAMBÉM (&&) se são os caracteres válidos INTERNOS (0NSWE)
	// se algum deles NEM VÁLIDO EM GERAL FOR (sei la, vai que alguem digite '3' ou 'z'),
	// retorna erro
	while(*map_line[char_counter])
	{
		if(!is_valid_char(*map_line[char_counter]))
			return(0);
		else
		{
			// se for o caracter de spawning, a gente grava a letra e as coordenadas na struct...
			if(ft_strchr(GAMER, *map_line[char_counter])
				&& !is_single_gamer(map, *map_line[char_counter], row, char_counter))
				return(0);
			// ou seja: é um caracter interno (0NSEW) mas NÃO ESTÁ cercado (tem espaço ou null ao redor)
			// daí dá erro, 
			if(ft_strchr(INTERNAL_CHAR, *map_line[char_counter]) && !check_is_closed(map_line, char_counter))
				return(0);
		}
		char_counter++;
	}
	return(1);
}

int is_map_open(t_map *map)
{
	int counter_string;

	counter_string = 0;
	while (counter_string < map->height)
	{
		// abaixo: se for a PRIMEIRA OU ÚLTIMA linha do mapa
		if((counter_string == 0 || counter_string == (map->height - 1))
			&& !is_wall(map->map[counter_string]))
			map_error(map);
		else
		{
			if (!check_map_interior(map, &map->map[counter_string], counter_string))
				map_error(map); //passar um numero especifico para o erro para personalizar a mensagem?
		}
	}
}


// int is_map_open(t_map *map)
// {
// 	int x_axis;
// 	int y_axis;
// 	int	skip_spaces;

// 	y_axis = 0;
// 	while(map->map[y_axis])
// 	{
// 		x_axis = 0;
// 		while (map->map[y_axis][x_axis])
// 		{
// 			if(map->map[y_axis][x_axis] == ' ')
// 			{
// 				// rodar até encontrar '1' (e atualizar a pos_x), senao dá erro
// 				skip_spaces = validate_row(map->map, x_axis, y_axis, ' ');
// 				if (skip_spaces < 0)
// 					return (skip_spaces);
// 				else
// 					x_axis += (skip_spaces - x_axis); //atualizar a posicao em x
// 			}
// 			else if (map->map[y_axis][x_axis] == '0')
// 			{
// 				// printf("Encontrou zero: %d e %d\n", y_axis, x_axis);
// 				skip_spaces = validate_row(map->map, x_axis, y_axis, '0');
// 				if (skip_spaces < 0)
// 					return (skip_spaces);
// 				else
// 					x_axis += (skip_spaces - x_axis);
// 			}
// 			x_axis++;
// 		}
// 		y_axis++;
// 	}
// 	return (0);
// }

int	validate_map(t_map *map)
{
	validate_rgb(map->floor);
	validate_rgb(map->ceilling);
	validate_texture(map);
	verif_char(map);
	if (is_map_open(map) < 0)
	{
		printf("Erro\nSeu mapa não está fechado!");
		exit(-30);
	}
	return (0);
}
/*
./cub3d ./src/maps/map.cub
*/