/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:00:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/24 15:18:27 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Initialise les vecteurs de direction et plan caméra selon l'orientation initiale
static void	init_player_direction(t_player *player)
{
	if (player->start_dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;  // FOV d'environ 66°
		player->plane_y = 0.0;
	}
	else if (player->start_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (player->start_dir == 'E')
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

// Extrait la position du joueur de la map et l'initialise
int	extract_player_position(t_game *game)
{
	int	row;
	int	col;
	int	player_found;

	player_found = 0;
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'N' || game->map[row][col] == 'S' 
				|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
			{
				if (player_found)
					return (print_error("Multiple players found in map"));
				
				// Stocker position (centre de la case)
				game->player.x = col + 0.5;
				game->player.y = row + 0.5;
				game->player.start_dir = game->map[row][col];
				
				// Remplacer le joueur par un espace libre dans la map
				game->map[row][col] = '0';
				
				player_found = 1;
			}
			col++;
		}
		row++;
	}
	
	if (!player_found)
		return (print_error("No player found in map"));
	
	// Initialiser les vecteurs de direction
	init_player_direction(&game->player);
	
	return (1);
}