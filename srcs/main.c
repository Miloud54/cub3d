/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:08:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/28 16:24:45 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	validate_args(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "Usage: ./cub3D map.cub\n", 23);
		return (0);
	}
	if (!is_valid_extension(av[1]))
		return (0);
	if (!file_exists(av[1]))
		return (print_error("File does not exist"));
	return (1);
}

static int	setup_parsing(char *filename, t_game *game)
{
	if (!parse_scene(filename, game) || !validate_map_structure(game)
		|| !validate_textures(&game->textures)
		|| !extract_player_position(game) || !extract_enemies(game))
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}

static int	setup_game(t_game *game)
{
	if (!init_game(game))
	{
		cleanup_game(game);
		return (0);
	}
	if (!load_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_mouse_hook(game->window, mouse_hook, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_expose_hook(game->window, render_loop, game);
	mlx_hook(game->window, 17, 0, close_game, game);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!validate_args(ac, av))
		return (1);
	if (!setup_parsing(av[1], &game))
		return (1);
	if (!setup_game(&game))
		return (1);
	setup_hooks(&game);
	render_frame(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
