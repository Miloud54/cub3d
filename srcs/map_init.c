/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:24:58 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 12:34:15 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	safe_mlx_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error\nInitializing mlx failed\n", 30);
		return (0);
	}
	return (1);
}

static int	init_window(t_game *game)
{
	int		width;
	int		height;

	width = game->map_width * TILE_SIZE;
	height = game->map_height * TILE_SIZE;
	game->window = mlx_new_window(game->mlx, width, height, "so_long!");
	if (!game->window)
	{
		write(2, "Error\nFailed to create new window\n", 34);
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
{
	if (!safe_mlx_init(game))
		return (0);
	if (!init_window(game))
	{
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		return (0);
	}
	return (1);
}