/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:45:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/25 18:40:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MINIMAP_SIZE 200
#define MINIMAP_TILE_SIZE 8
#define MINIMAP_OFFSET 20

static void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	pixel = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	draw_minimap_tile(t_game *game, int map_x, int map_y, int color)
{
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	screen_x = MINIMAP_OFFSET + (map_x * MINIMAP_TILE_SIZE);
	screen_y = MINIMAP_OFFSET + (map_y * MINIMAP_TILE_SIZE);
	y = 0;
	while (y < MINIMAP_TILE_SIZE)
	{
		x = 0;
		while (x < MINIMAP_TILE_SIZE)
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

	if (y < 0 || y >= game->map_height || x < 0 || !game->map[y][x])
		return (0x000000);
	tile = game->map[y][x];
	if (tile == '1')
		return (0xFFFFFF);
	if (tile == '0')
		return (0x808080);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0x808080);
	return (0x000000);
}

static void	draw_player_on_minimap(t_game *game)
{
	int		player_screen_x;
	int		player_screen_y;
	int		x;
	int		y;
	int		size;

	size = 3;
	player_screen_x = MINIMAP_OFFSET + (int)(game->player.x * MINIMAP_TILE_SIZE)
		- size / 2;
	player_screen_y = MINIMAP_OFFSET + (int)(game->player.y * MINIMAP_TILE_SIZE)
		- size / 2;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_to_image(game, player_screen_x + x, player_screen_y + y,
				0xFF0000);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	max_tiles_x;
	int	max_tiles_y;

	max_tiles_x = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	max_tiles_y = MINIMAP_SIZE / MINIMAP_TILE_SIZE;
	y = 0;
	while (y < max_tiles_y && y < game->map_height)
	{
		x = 0;
		while (x < max_tiles_x && x < game->map_width)
		{
			color = get_minimap_tile_color(game, x, y);
			draw_minimap_tile(game, x, y, color);
			x++;
		}
		y++;
	}
	draw_player_on_minimap(game);
}
