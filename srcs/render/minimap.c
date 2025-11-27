/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/27 14:28:52 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MINIMAP_RADIUS 5
#define MINIMAP_TILE_SIZE_MINI 6

static void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	pixel = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	draw_minimap_tile(t_game *game, int screen_x, int screen_y, int color)
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
#if BONUS
	if (tile == 'D')
		return (0x8B5A2B);
	if (tile == 'd')
		return (0xC8A165);
#endif
	if (tile == '0')
		return (0x808080);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0x808080);
	return (0x000000);
}

static void	draw_player_on_minimap(t_game *game)
{
	int		center_x;
	int		center_y;
	int		x;
	int		y;
	int		size;

	size = 3;
	center_x = MINIMAP_OFFSET + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE_MINI);
	center_y = MINIMAP_OFFSET + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE_MINI);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_to_image(game, center_x - size / 2 + x, 
				center_y - size / 2 + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_game *game)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;
	int	player_map_x;
	int	player_map_y;
	int	x_offset;
	int	y_offset;

	player_map_x = (int)game->player.x;
	player_map_y = (int)game->player.y;
	map_y = player_map_y - MINIMAP_RADIUS;
	while (map_y <= player_map_y + MINIMAP_RADIUS)
	{
		map_x = player_map_x - MINIMAP_RADIUS;
		while (map_x <= player_map_x + MINIMAP_RADIUS)
		{
			color = get_minimap_tile_color(game, map_x, map_y);
			if (color != 0x000000)
			{
				x_offset = map_x - (player_map_x - MINIMAP_RADIUS);
				y_offset = map_y - (player_map_y - MINIMAP_RADIUS);
				screen_x = MINIMAP_OFFSET + (x_offset * MINIMAP_TILE_SIZE_MINI);
				screen_y = MINIMAP_OFFSET + (y_offset * MINIMAP_TILE_SIZE_MINI);
				draw_minimap_tile(game, screen_x, screen_y, color);
			}
			map_x++;
		}
		map_y++;
	}
	draw_player_on_minimap(game);
}
