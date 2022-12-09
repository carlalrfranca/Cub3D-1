/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:53:11 by lfranca-          #+#    #+#             */
/*   Updated: 2022/12/09 18:10:58 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/* loop principal pra verificar o mapa: */
/*	1)função recebe o mapa */
/*	2)loop sobre cada STRING do mapa */
/*	3)verifica que a primeira string seja parede ('1's ou espaços vazios) */
/*	4)nas demais (até ANTES DA ÚLTIMA), enviar para uma função */
/*		que vai verificar se o caracter é valido (1 0NSEW) && se é caracter */
/*		interno (0NSWE) - tirando parede e espaço vazio */
/*		- se for, verifica AO REDOR dele, e se tiver espaço vazio/nulo, */
/*		RETORNA ERRO (e dá mapa inválido), */
/*		senão, prossegue. */
/*	5)Dentro do loop, terá uma condição pra se for */
/*	a ÚLTIMA LINHA (i == 0 || i == (map->height - 1)) */
/*	que será enviada para a mesma função que recebeu a primeira linha e */
/*	verifica se é parede ('1's ou espaços vazios) */
/*	----------------------- */
/*	OBS: Precisamos GARANTIR que haja apenas UM PERSONAGEM, */
/*	se houver mais, DÁ ERRO! (macro GAMER[NSEW]?) */
/*	OBS2: A gente também tem que invalidar o mapa caso */
/*	ele tenha LINHAS VAZIAS NO MEIO.. */
int	is_wall(char *map_line, int map_width)
{
	int	char_counter;

	char_counter = 0;
	// proteção aqui caso a ultima linha do mapa seja uma linha vazia...
	while (char_counter < map_width)
	{
		if (!ft_strchr("1 ", map_line[char_counter]))
			return (0);
		char_counter++;
	}
	return (1);
}

/*função verifica: */
/* Primeiro if: se for interno, verifica o caractere anterior */
/* Segundo if: se for menor que a extremidade à direita, */
/*	podendo ser interno e tambem a extremidade esquerda (0) */
/* Ultimo if: se for a borda (que deve ser parede, e caso nao seja, */
/* significa que a função que verifica os carateres internos */
/* vai delatá-la) entao é só devolver que é parede */
int	is_eroded_internal_wall(char **map_line, int char_counter)
{
	if (char_counter != 0 && char_counter < ((int)ft_strlen(map_line[0]) - 1))
	{
		if (map_line[0][char_counter - 1] == '1')
			return (0);
	}
	if (char_counter < ((int)ft_strlen(map_line[0]) - 1))
	{
		if (map_line[0][char_counter + 1] == '1'
			|| map_line[-1][char_counter] == '1'
			|| map_line[1][char_counter] == '1')
			return (0);
	}
	if (char_counter == ((int)ft_strlen(map_line[0]) - 1))
		return (0);
	return (1);
}

/*
    ** pra verificar as linhas anterior e posteriores, precisa acessar
    ** o ENDEREÇO em (-1) e (+1) / e (0).. por isso precisa
    ** passar a linha por ENDEREÇO/PONTEIRO. Se for por valor, será
    ** apenas uma CÓPIA do valor da string EM OUTRO ESPAÇO DE MEMORIA,
    ** e NAO DARÁ PRA ACESSAR AS LINHAS ANTERIORES/POSTERIORES DO MAPA
	** Já que essa é uma verificação INTERNA do mapa, verifica se a linha
	** atual, a anterior ou a seguinte está vazia, se sim, dá erro.
	** Primeiro if: quer dizer que caracteres internos estão na borda
*/
int	check_is_closed(char **map_line, int char_counter)
{
	int	prev_index;
	int	next_index;

	prev_index = char_counter - 1;
	next_index = char_counter + 1;
	if (char_counter == 0 || char_counter == ((int)ft_strlen(map_line[0]) - 1))
		return (0);
	if (is_empty_line(map_line[0]) || is_empty_line(map_line[-1]) || is_empty_line(map_line[1]))
		return (0);
	if (!map_line[0][prev_index] || ft_is_space(map_line[0][prev_index]))
		return (0);
	if (!map_line[0][next_index] || ft_is_space(map_line[0][next_index]))
		return (0);
	if (!map_line[-1][char_counter] || ft_is_space(map_line[-1][char_counter]))
		return (0);
	if (!map_line[-1][prev_index] || ft_is_space(map_line[-1][prev_index]))
		return (0);
	if (!map_line[-1][next_index] || ft_is_space(map_line[-1][next_index]))
		return (0);
	if (!map_line[1][char_counter] || ft_is_space(map_line[1][char_counter]))
		return (0);
	if (!map_line[1][prev_index] || ft_is_space(map_line[1][prev_index]))
		return (0);
	if (!map_line[1][next_index] || ft_is_space(map_line[1][next_index]))
		return (0);
	return (1);
}

/**/
/* aqui verificaremos apenas se tem caracteres validos */
/*(o que inclui espaço e 1..) */
/* MAS TAMBÉM (&&) se são os caracteres válidos INTERNOS (0NSWE) */
/* se algum deles NEM VÁLIDO EM GERAL FOR */
/* (sei la, vai que alguem digite '3' ou 'z'), */
/* retorna erro */
/* - se for o caracter de spawning, a gente grava */
/* 	 a letra e as coordenadas na struct */
/* - se for interno e caracteres (0NEWS), verificar se eles */
/*   nao estao com espaço ao redor  */
/* - if pra verificar se , na ocorrencia de paredes internas, */
/*	elas nao estao cercadas com 0's: acima, */
/* imediatamente dos lados e abaixo */
/* (celula isolada de parede dá erro) como a seguir: */
/* - 0 - */
/* 0 1 0 */
/* - 0 - */
int	check_map_interior(t_map *map, char **map_line, int row)
{
	int		char_counter;
	char	*trimmed_line;

	char_counter = 0;
	if (ft_strlen(map_line[0]) == 0)
		return (0);
	trimmed_line = ft_strtrim(map_line[0], " \t");
	if (ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return (0);
	}
	free(trimmed_line);
	while (map_line[0][char_counter])
	{
		if (!is_valid_char(map_line[0][char_counter]))
			return (0);
		else
		{
			if (ft_strchr(GAMER, map_line[0][char_counter])
				&& !is_single_gamer(map, map_line[0][char_counter], row, char_counter))
				return (0);
			if (ft_strchr(INTERNAL_CHAR, map_line[0][char_counter]) && !check_is_closed(map_line, char_counter))
				return (0);
			else if (map_line[0][char_counter] == '1' && is_eroded_internal_wall(map_line, char_counter))
				return (0);
		}
		char_counter++;
	}
	return (1);
}

int	is_map_open(t_map *map)
{
	int	counter_string;

	counter_string = 0;
	while (counter_string < map->height)
	{
		if (is_first_last_row(counter_string, map->height)
			&& !is_wall(map->map[counter_string], map->width))
			map_error(map);
		else if (!is_first_last_row(counter_string, map->height))
		{
			if (!check_map_interior(map, &map->map[counter_string], counter_string))
				map_error(map);
		}
		counter_string++;
	}
	return (1);
}
