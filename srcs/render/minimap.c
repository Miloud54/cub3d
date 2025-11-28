/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/28 15:39:40 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	pixel = game->img_addr + (y * game->img_line_len
			+ x * (game->img_bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	draw_minimap_tile(t_game *game, int screen_x, int screen_y,
	int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_TILE_SIZE_MINI)
	{
		x = 0;
		while (x < MINIMAP_TILE_SIZE_MINI)
		{
			put_pixel_to_image(game, screen_x + x, screen_y + y, color);
			x++;
		}
		y++;
	}
}

static int	get_minimap_tile_color(t_game *game, int x, int y)
{
	char	tile;

	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0x000000);
	if (!game->map[y] || !game->map[y][x])
		return (0x000000);
	tile = game->map[y][x];
	if (tile == '1')
		return (0xFFFFFF);
	if (BONUS && tile == 'D')
		return (0x8B5A2B);
	if (BONUS && tile == 'd')
		return (0xC8A165);
	if (tile == '0')
		return (0x808080);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0x808080);
	return (0x000000);
}

static void	render_minimap_tiles(t_game *game, int player_x, int player_y)
{
	int	map_x;
	int	map_y;
	int	color;
	int	screen_coords[2];

	map_y = player_y - MINIMAP_RADIUS;
	while (map_y <= player_y + MINIMAP_RADIUS)
	{
		map_x = player_x - MINIMAP_RADIUS;
		while (map_x <= player_x + MINIMAP_RADIUS)
		{
			color = get_minimap_tile_color(game, map_x, map_y);
			if (color != 0x000000)
			{
				screen_coords[0] = MINIMAP_OFFSET + (map_x - player_x
						+ MINIMAP_RADIUS) * MINIMAP_TILE_SIZE_MINI;
				screen_coords[1] = MINIMAP_OFFSET + (map_y - player_y
						+ MINIMAP_RADIUS) * MINIMAP_TILE_SIZE_MINI;
				draw_minimap_tile(game, screen_coords[0], screen_coords[1],
					color);
			}
			map_x++;
		}
		map_y++;
	}
}

void	render_minimap(t_game *game)
{
	int	player_map_x;
	int	player_map_y;
	int	center_x;
	int	center_y;
	int	coords[2];

	player_map_x = (int)game->player.x;
	player_map_y = (int)game->player.y;
	render_minimap_tiles(game, player_map_x, player_map_y);
	center_x = MINIMAP_OFFSET + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE_MINI);
	center_y = MINIMAP_OFFSET + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE_MINI);
	coords[1] = 0;
	while (coords[1] < 3)
	{
		coords[0] = 0;
		while (coords[0] < 3)
		{
			put_pixel_to_image(game, center_x - 1 + coords[0],
				center_y - 1 + coords[1], 0xFF0000);
			coords[0]++;
		}
		coords[1]++;
	}
}
