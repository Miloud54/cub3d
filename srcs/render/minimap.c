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

static int	minimap_tile_color(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0x000000);
	if (!game->map[y] || !game->map[y][x])
		return (0x000000);
	if (game->map[y][x] == '1')
		return (0xFFFFFF);
	if (BONUS && game->map[y][x] == 'D')
		return (0x8B5A2B);
	if (BONUS && game->map[y][x] == 'd')
		return (0xC8A165);
	if (game->map[y][x] == '0' || game->map[y][x] == 'N'
		|| game->map[y][x] == 'S' || game->map[y][x] == 'E'
		|| game->map[y][x] == 'W')
		return (0x808080);
	return (0x000000);
}

static void	render_minimap_tiles(t_game *game, int player_x, int player_y)
{
	int	map_x;
	int	map_y;
	int	color;
	int	idx;

	map_y = player_y - MINIMAP_RADIUS - 1;
	while (++map_y <= player_y + MINIMAP_RADIUS)
	{
		map_x = player_x - MINIMAP_RADIUS - 1;
		while (++map_x <= player_x + MINIMAP_RADIUS)
		{
			color = minimap_tile_color(game, map_x, map_y);
			if (color != 0x000000)
			{
				idx = -1;
				while (++idx < MINIMAP_TILE_SIZE_MINI * MINIMAP_TILE_SIZE_MINI)
					put_pixel_to_image(game, MINIMAP_OFFSET + (map_x - player_x
							+ MINIMAP_RADIUS) * MINIMAP_TILE_SIZE_MINI
						+ (idx % MINIMAP_TILE_SIZE_MINI), MINIMAP_OFFSET
						+ (map_y - player_y + MINIMAP_RADIUS)
						* MINIMAP_TILE_SIZE_MINI
						+ (idx / MINIMAP_TILE_SIZE_MINI), color);
			}
		}
	}
}

static void	render_minimap_enemies(t_game *game, int player_x, int player_y)
{
	int		i;
	int		screen_x;
	int		screen_y;
	int		mark;

	if (!BONUS || game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (fabs(game->enemies[i].x - player_x) <= MINIMAP_RADIUS
			&& fabs(game->enemies[i].y - player_y) <= MINIMAP_RADIUS)
		{
			screen_x = MINIMAP_OFFSET + (int)((game->enemies[i].x - player_x
						+ MINIMAP_RADIUS) * MINIMAP_TILE_SIZE_MINI);
			screen_y = MINIMAP_OFFSET + (int)((game->enemies[i].y - player_y
						+ MINIMAP_RADIUS) * MINIMAP_TILE_SIZE_MINI);
			mark = -1;
			while (++mark < 9)
				put_pixel_to_image(game, screen_x - 1 + (mark % 3),
					screen_y - 1 + (mark / 3), 0x00FF00);
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	player_map_x;
	int	player_map_y;
	int	center_idx;

	player_map_x = (int)game->player.x;
	player_map_y = (int)game->player.y;
	render_minimap_tiles(game, player_map_x, player_map_y);
	render_minimap_enemies(game, player_map_x, player_map_y);
	center_idx = -1;
	while (++center_idx < 9)
		put_pixel_to_image(game, MINIMAP_OFFSET + MINIMAP_RADIUS
			* MINIMAP_TILE_SIZE_MINI - 1 + (center_idx % 3), MINIMAP_OFFSET
			+ MINIMAP_RADIUS * MINIMAP_TILE_SIZE_MINI - 1 + (center_idx / 3),
			0xFF0000);
}
