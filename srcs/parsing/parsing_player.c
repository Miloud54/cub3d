/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:00:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/24 16:55:41 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* ************************************************************************** */
/*                         init_player_direction                              */
/* ************************************************************************** */

static void	set_east_west_direction(t_player *player)
{
	if (player->start_dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (player->start_dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

static void	init_player_direction(t_player *player)
{
	if (player->start_dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (player->start_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (player->start_dir == 'E' || player->start_dir == 'W')
		set_east_west_direction(player);
}

/* ************************************************************************** */
/*                          extract_player_position                           */
/* ************************************************************************** */

// Extracts player's position from the map and initializes it
// It stocks position as the middle of the tile ("+0.5"), and then
// it puts a free space instead of the player in the map. To finish,
// it initializes the direction vectors by calling init_player_direction()

static int	process_player_tile(t_game *game, int row, int col, int *found)
{
	if (*found)
		return (print_error("Multiple players found in map"));
	game->player.x = col + 0.5;
	game->player.y = row + 0.5;
	game->player.start_dir = game->map[row][col];
	game->map[row][col] = '0';
	*found = 1;
	return (1);
}

static int	scan_row_for_player(t_game *game, int row, int *found)
{
	int	col;

	col = 0;
	while (game->map[row][col])
	{
		if (game->map[row][col] == 'N' || game->map[row][col] == 'S'
			|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
		{
			if (!process_player_tile(game, row, col, found))
				return (0);
		}
		col++;
	}
	return (1);
}

// Main function: extracts player from map and initializes position/direction
// Validates single player existence, centers position in tile, sets up vectors
int	extract_player_position(t_game *game)
{
	int	row;
	int	player_found;

	player_found = 0;
	row = 0;
	while (row < game->map_height)
	{
		if (!scan_row_for_player(game, row, &player_found))
			return (0);
		row++;
	}
	if (!player_found)
		return (print_error("No player found in map"));
	init_player_direction(&game->player);
	return (1);
}
