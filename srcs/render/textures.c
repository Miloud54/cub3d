/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:42:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 16:31:19 by edidier          ###   ########.fr       */
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
	data = mlx_get_data_addr(image, &game->textures.bpp,
			line_len, &game->textures.endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, image);
		return (print_error("Failed to access texture data"));
	}
	*img = image;
	*addr = data;
	return (1);
}

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
	game->textures.north_img = NULL;
	game->textures.south_img = NULL;
	game->textures.west_img = NULL;
	game->textures.east_img = NULL;
	game->textures.north_addr = NULL;
	game->textures.south_addr = NULL;
	game->textures.west_addr = NULL;
	game->textures.east_addr = NULL;
}
