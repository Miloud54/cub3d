/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:07:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/11/28 16:07:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_one_texture(t_game *game, char *path, t_tex_load *tex)
{
	void	*image;
	char	*data;

	image = mlx_xpm_file_to_image(game->mlx, path, tex->w, tex->h);
	if (!image)
		return (print_error("Failed to load texture image"));
	data = mlx_get_data_addr(image, &game->textures.bpp, tex->line_len,
			&game->textures.endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, image);
		return (print_error("Failed to access texture data"));
	}
	*(tex->img) = image;
	*(tex->addr) = data;
	return (1);
}

int	load_door_texture(t_game *game)
{
	t_tex_load	tex;

	tex = (t_tex_load){&game->textures.door_img, &game->textures.door_addr,
		&game->textures.door_w, &game->textures.door_h,
		&game->textures.door_line_len};
	return (load_one_texture(game, "textures/door1.xpm", &tex));
}

int	has_bonus_features(void)
{
	return (1);
}

void	destroy_wall_textures(t_game *game)
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

void	destroy_bonus_textures(t_game *game)
{
	int	i;

	if (game->textures.door_img)
		mlx_destroy_image(game->mlx, game->textures.door_img);
	i = 0;
	while (i < 4)
	{
		if (game->textures.enemy_img[i])
			mlx_destroy_image(game->mlx, game->textures.enemy_img[i]);
		i++;
	}
	game->textures.door_img = NULL;
	game->textures.door_addr = NULL;
	ft_bzero(game->textures.enemy_img, sizeof(game->textures.enemy_img));
	ft_bzero(game->textures.enemy_addr, sizeof(game->textures.enemy_addr));
	ft_bzero(game->textures.enemy_line_len,
		sizeof(game->textures.enemy_line_len));
}
