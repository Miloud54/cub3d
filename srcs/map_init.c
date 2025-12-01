/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:24:58 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/28 13:56:50 by edidier          ###   ########.fr       */
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

static int	allocate_bonus_buffers(t_game *game, int width)
{
	if (!BONUS)
	{
		(void)game;
		(void)width;
		return (1);
	}
	game->z_buffer = malloc(sizeof(double) * width);
	if (!game->z_buffer)
		return (print_error("Failed to allocate z-buffer"));
	return (1);
}

static int	setup_window_image(t_game *game, int width, int height)
{
	game->window = mlx_new_window(game->mlx, width, height, "cub3D");
	game->win_w = width;
	game->win_h = height;
	if (!game->window)
	{
		write(2, "Error\nFailed to create new window\n", 34);
		return (0);
	}
	game->img = mlx_new_image(game->mlx, width, height);
	if (!game->img)
		return (print_error("Failed to create render buffer"));
	game->img_addr = mlx_get_data_addr(game->img, &game->img_bpp,
			&game->img_line_len, &game->img_endian);
	if (!game->img_addr)
		return (print_error("Failed to access render buffer"));
	return (1);
}

static int	init_window(t_game *game)
{
	int	width;
	int	height;

	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!setup_window_image(game, width, height))
		return (0);
	if (!allocate_bonus_buffers(game, width))
		return (0);
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
