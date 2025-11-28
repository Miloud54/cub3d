/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:42:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 13:56:36 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	load_one_texture(t_game *game, char *path, void **img, char **addr,
		int *w, int *h, int *line_len)
{
	void	*image;
	char	*data;

	image = mlx_xpm_file_to_image(game->mlx, path, w, h);
	if (!image)
		return (print_error("Failed to load texture image"));
	data = mlx_get_data_addr(image, &game->textures.bpp, line_len,
			&game->textures.endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, image);
		return (print_error("Failed to access texture data"));
	}
	*img = image;
	*addr = data;
	return (1);
}

#if BONUS
static int	load_enemy_textures(t_game *game)
{
	static char	*paths[ENEMY_FRAME_COUNT] = {"textures/enemy1.xpm",
			"textures/enemy2.xpm", "textures/enemy3.xpm",
			"textures/enemy4.xpm"};
	int			i;

	i = 0;
	while (i < ENEMY_FRAME_COUNT)
	{
		if (!load_one_texture(game, paths[i], &game->textures.enemy_img[i],
				&game->textures.enemy_addr[i], &game->textures.enemy_w,
				&game->textures.enemy_h, &game->textures.enemy_line_len[i]))
			return (0);
		i++;
	}
	return (1);
}
#endif

int	load_textures(t_game *game)
{
	if (!load_one_texture(game, game->textures.north, &game->textures.north_img,
			&game->textures.north_addr, &game->textures.north_w,
			&game->textures.north_h, &game->textures.north_line_len))
		return (0);
	if (!load_one_texture(game, game->textures.south, &game->textures.south_img,
			&game->textures.south_addr, &game->textures.south_w,
			&game->textures.south_h, &game->textures.south_line_len))
		return (0);
	if (!load_one_texture(game, game->textures.west, &game->textures.west_img,
			&game->textures.west_addr, &game->textures.west_w,
			&game->textures.west_h, &game->textures.west_line_len))
		return (0);
	if (!load_one_texture(game, game->textures.east, &game->textures.east_img,
			&game->textures.east_addr, &game->textures.east_w,
			&game->textures.east_h, &game->textures.east_line_len))
		return (0);
#if BONUS
	if (!load_one_texture(game, "textures/door1.xpm", &game->textures.door_img,
			&game->textures.door_addr, &game->textures.door_w,
			&game->textures.door_h, &game->textures.door_line_len))
		return (0);
	if (!load_enemy_textures(game))
		return (0);
#endif
	return (1);
}

void	destroy_texture_images(t_game *game)
{
	if (game->textures.north_img)
		mlx_destroy_image(game->mlx, game->textures.north_img);
	if (game->textures.south_img)
		mlx_destroy_image(game->mlx, game->textures.south_img);
	if (game->textures.west_img)
		mlx_destroy_image(game->mlx, game->textures.west_img);
	if (game->textures.east_img)
		mlx_destroy_image(game->mlx, game->textures.east_img);
#if BONUS
	if (game->textures.door_img)
		mlx_destroy_image(game->mlx, game->textures.door_img);
	if (game->textures.enemy_img[0])
		mlx_destroy_image(game->mlx, game->textures.enemy_img[0]);
	if (game->textures.enemy_img[1])
		mlx_destroy_image(game->mlx, game->textures.enemy_img[1]);
	if (game->textures.enemy_img[2])
		mlx_destroy_image(game->mlx, game->textures.enemy_img[2]);
	if (game->textures.enemy_img[3])
		mlx_destroy_image(game->mlx, game->textures.enemy_img[3]);
#endif
	game->textures.north_img = NULL;
	game->textures.south_img = NULL;
	game->textures.west_img = NULL;
	game->textures.east_img = NULL;
	game->textures.north_addr = NULL;
	game->textures.south_addr = NULL;
	game->textures.west_addr = NULL;
	game->textures.east_addr = NULL;
#if BONUS
	game->textures.door_img = NULL;
	game->textures.door_addr = NULL;
	ft_bzero(game->textures.enemy_img, sizeof(game->textures.enemy_img));
	ft_bzero(game->textures.enemy_addr, sizeof(game->textures.enemy_addr));
	ft_bzero(game->textures.enemy_line_len,
		sizeof(game->textures.enemy_line_len));
#endif
}
