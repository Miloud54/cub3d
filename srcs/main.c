/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:08:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/28 13:56:48 by edidier          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!validate_args(ac, av))
		return (1);
	if (!parse_scene(av[1], &game) || !validate_map_structure(&game)
		|| !validate_textures(&game.textures) || !extract_player_position(&game)
#if BONUS
		|| !extract_enemies(&game)
#endif
	)
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!load_textures(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	mlx_mouse_hook(game.window, mouse_hook, &game);
	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_expose_hook(game.window, render_loop, &game);
	render_frame(&game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
