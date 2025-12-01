/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:04:16 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/12/01 13:42:23 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	ft_memset(textures, 0, sizeof(t_textures));
}

#if BONUS

# define BONUS_ENABLED 1

#else

# define BONUS_ENABLED 0

#endif

static void	destroy_graphics(t_game *game)
{
	if (game->mlx)
		destroy_texture_images(game);
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

static void	free_bonus_data(t_game *game)
{
	if (!BONUS_ENABLED)
		return ;
	if (game->enemies)
		free(game->enemies);
	if (game->z_buffer)
		free(game->z_buffer);
}

void	cleanup_game(t_game *game)
{
	destroy_graphics(game);
	if (game->map)
		free_map(game->map);
	if (game->exterior_map)
		free_exterior_map(game->exterior_map, game->map_height);
	free_bonus_data(game);
	free_textures(&game->textures);
}
