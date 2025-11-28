/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:30:00 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 13:56:08 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#if BONUS

static void	init_enemy_direction(t_enemy *enemy, int index)
{
	double	len;

	if (index % 2 == 0)
		enemy->dir_x = 1.0;
	else
		enemy->dir_x = -1.0;
	if (index % 3 == 0)
		enemy->dir_y = 0.65;
	else
		enemy->dir_y = -0.65;
	len = sqrt(enemy->dir_x * enemy->dir_x + enemy->dir_y * enemy->dir_y);
	if (len > 0.0)
	{
		enemy->dir_x /= len;
		enemy->dir_y /= len;
	}
}

static int	count_enemies(t_game *game)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == ENEMY_SPAWN_CHAR)
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

static void	fill_enemies(t_game *game)
{
	int	row;
	int	col;
	int	idx;

	row = 0;
	idx = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == ENEMY_SPAWN_CHAR)
			{
				game->enemies[idx].x = col + 0.5;
				game->enemies[idx].y = row + 0.5;
				init_enemy_direction(&game->enemies[idx], idx);
				game->enemies[idx].speed = ENEMY_MOVE_SPEED;
				game->enemies[idx].frame = 0;
				game->enemies[idx].frame_timer = 0.0;
				game->map[row][col] = '0';
				idx++;
			}
			col++;
		}
		row++;
	}
}

int	extract_enemies(t_game *game)
{
	int	count;

	count = count_enemies(game);
	if (count == 0)
		return (1);
	game->enemies = malloc(sizeof(t_enemy) * count);
	if (!game->enemies)
		return (print_error("Failed to allocate enemies"));
	game->enemy_count = count;
	fill_enemies(game);
	return (1);
}

#endif
