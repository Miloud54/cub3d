/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:02:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/24 15:55:26 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_cell(char **map, int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return (0);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (0);
	return (map[row][col] == '0' || is_player(map[row][col]));
}

static int	is_wall_or_space(char **map, int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return (0);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (0);
	return (map[row][col] == '1' || map[row][col] == ' ');
}

static int	check_cell_closure(char **map, int height, int row, int col)
{
	if (!is_wall_or_space(map, height, row - 1, col) && !is_valid_cell(map, height, row - 1, col))
		return (0);
	if (!is_wall_or_space(map, height, row + 1, col) && !is_valid_cell(map, height, row + 1, col))
		return (0);
	if (!is_wall_or_space(map, height, row, col - 1) && !is_valid_cell(map, height, row, col - 1))
		return (0);
	if (!is_wall_or_space(map, height, row, col + 1) && !is_valid_cell(map, height, row, col + 1))
		return (0);
	return (1);
}

static int	validate_borders(t_game *game)
{
	int	row;
	int	col;
	int	len;
	int	max_width;

	max_width = 0;
	for (row = 0; row < game->map_height; row++)
	{
		len = ft_strlen(game->map[row]);
		if (len > max_width)
			max_width = len;
	}
	for (row = 0; row < game->map_height; row++)
	{
		len = ft_strlen(game->map[row]);
		for (col = 0; col < len; col++)
		{
			if (game->map[row][col] == '0' || is_player(game->map[row][col]))
			{
				if (len != max_width)
					return (print_error("Map not rectangular: game lines must be complete"));
				
				if (row == 0 || row == game->map_height - 1)
					return (print_error("Map not closed: game space on border"));
				if (col == 0 || col >= len - 1)
					return (print_error("Map not closed: game space on border"));
				if (!check_cell_closure(game->map, game->map_height, row, col))
					return (print_error("Map not closed: game space can escape"));
			}
		}
	}
	return (1);
}

static int	validate_rectangular_closure(t_game *game)
{
	int	row;
	int	col;
	int	len;
	int	max_width;

	// Trouver la largeur maximale
	max_width = 0;
	for (row = 0; row < game->map_height; row++)
	{
		len = ft_strlen(game->map[row]);
		if (len > max_width)
			max_width = len;
	}

	// Vérifier que les bordures du rectangle maximal sont des murs
	// Première ligne
	len = ft_strlen(game->map[0]);
	if (len != max_width)
		return (print_error("Map not properly closed: first line incomplete"));
	for (col = 0; col < len; col++)
		if (game->map[0][col] != '1' && game->map[0][col] != ' ')
			return (print_error("Map not closed: top border must be walls"));

	// Dernière ligne  
	len = ft_strlen(game->map[game->map_height - 1]);
	if (len != max_width)
		return (print_error("Map not properly closed: last line incomplete"));
	for (col = 0; col < len; col++)
		if (game->map[game->map_height - 1][col] != '1' && game->map[game->map_height - 1][col] != ' ')
			return (print_error("Map not closed: bottom border must be walls"));

	// Colonnes gauche et droite
	for (row = 0; row < game->map_height; row++)
	{
		len = ft_strlen(game->map[row]);
		if (len > 0 && game->map[row][0] != '1' && game->map[row][0] != ' ')
			return (print_error("Map not closed: left border must be walls"));
		if (len == max_width && game->map[row][len - 1] != '1' && game->map[row][len - 1] != ' ')
			return (print_error("Map not closed: right border must be walls"));
		if (len < max_width)
			return (print_error("Map not properly closed: incomplete line"));
	}
	return (1);
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
	if (!validate_rectangular_closure(game))
		return (0);
	if (!validate_borders(game))
		return (0);
	if (!scan_map(game, &player_count))
		return (0);
	if (player_count != 1)
		return (print_error("Map must contain exactly one player"));
	return (1);
}
