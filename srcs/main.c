/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:08:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 16:14:15 by bde-la-p         ###   ########.fr       */
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
	game.map = load_map(av[1]);
	if (!game.map)
		return (1);
	// Parser et valider les textures --- probablement a remettre ailleurs dans un check general du parsing !
	if (!parse_textures(av[1], &game.textures) || !validate_textures(&game.textures))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!parse_colors(av[1], &game.floor_color, &game.ceiling_color))
	{
		cleanup_game(&game);
		return (1);
	}
	
	if (!init_game(&game))
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
