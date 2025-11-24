/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 15:39:28 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	get_tile_color(t_game *game, char tile, int row, int col)
{
	if (tile == '1')
		return (0x505050);
	if (tile == ' ')
	{
		// Espace intérieur = mur, espace extérieur = noir
		if (is_exterior_space(game, row, col))
			return (0x000000);
		else
			return (0x505050);
	}
	if (tile == '0')
		return (game->floor_color);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0xFF0000);
	return (game->ceiling_color);
}

static void	draw_tile(t_game *game, int row, int col, int color)
{
	int	y;
	int	x;
	int	start_x;
	int	start_y;

	start_x = col * TILE_SIZE;
	start_y = row * TILE_SIZE;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->window, start_x + x, start_y + y,
				color);
			x++;
		}
		y++;
	}
}

int	render_map(t_game *game)
{
	int	row;
	int	col;
	int	color;

	if (!game->mlx || !game->window || !game->map)
		return (0);
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			color = get_tile_color(game, game->map[row][col], row, col);
			draw_tile(game, row, col, color);
			col++;
		}
		row++;
	}
	return (1);
}
