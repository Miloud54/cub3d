/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:08:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/21 12:18:23 by edidier          ###   ########.fr       */
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
		|| !validate_textures(&game.textures))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!render_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_key_hook(game.window, handle_input, &game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	free_textures(&game.textures);
	return (0);
}
