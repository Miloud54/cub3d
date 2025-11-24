/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:02:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/21 12:18:04 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_void(char **map, int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return (1);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (0); // treat missing columns as implicit walls
	// Les espaces sont traités comme des murs implicites, pas comme du vide
	// Seuls les caractères inexistants (hors limites) sont considérés comme void
	return (0);
}

static int	validate_cell(char **map, int height, int row, int col)
{
	int	len;

	len = ft_strlen(map[row]);
	if (row == 0 || row == height - 1)
		return (print_error("Map not closed vertically"));
	if (col == 0 || col >= len - 1)
		return (print_error("Map not closed horizontally"));
	if (is_void(map, height, row - 1, col) || is_void(map, height, row + 1, col)
		|| is_void(map, height, row, col - 1) || is_void(map, height, row, col
			+ 1))
		return (print_error("Map has open space"));
	return (1);
}

static int	scan_map(t_game *game, int *player_count)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (is_player(game->map[row][col]))
				(*player_count)++;
			// Valider seulement les cellules '0' et les joueurs, pas les espaces ni les murs
			if ((game->map[row][col] == '0' || is_player(game->map[row][col]))
				&& !validate_cell(game->map, game->map_height, row, col))
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	validate_map_structure(t_game *game)
{
	int	player_count;

	player_count = 0;
	if (!scan_map(game, &player_count))
		return (0);
	if (player_count != 1)
		return (print_error("Map must contain exactly one player"));
	return (1);
}
