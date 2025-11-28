/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:42:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 16:13:38 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	load_enemy_textures(t_game *game)
{
	static char	*paths[4] = {"textures/enemy1.xpm",
		"textures/enemy2.xpm", "textures/enemy3.xpm",
		"textures/enemy4.xpm"};
	int			i;
	t_tex_load	tex;

	i = 0;
	while (i < 4)
	{
		tex = (t_tex_load){&game->textures.enemy_img[i],
			&game->textures.enemy_addr[i], &game->textures.enemy_w,
			&game->textures.enemy_h, &game->textures.enemy_line_len[i]};
		if (!load_one_texture(game, paths[i], &tex))
			return (0);
		i++;
	}
	return (1);
}

static int	load_wall_textures(t_game *game)
{
	t_tex_load	tex;

	tex = (t_tex_load){&game->textures.north_img, &game->textures.north_addr,
		&game->textures.north_w, &game->textures.north_h,
		&game->textures.north_line_len};
	if (!load_one_texture(game, game->textures.north, &tex))
		return (0);
	tex = (t_tex_load){&game->textures.south_img, &game->textures.south_addr,
		&game->textures.south_w, &game->textures.south_h,
		&game->textures.south_line_len};
	if (!load_one_texture(game, game->textures.south, &tex))
		return (0);
	tex = (t_tex_load){&game->textures.west_img, &game->textures.west_addr,
		&game->textures.west_w, &game->textures.west_h,
		&game->textures.west_line_len};
	if (!load_one_texture(game, game->textures.west, &tex))
		return (0);
	tex = (t_tex_load){&game->textures.east_img, &game->textures.east_addr,
		&game->textures.east_w, &game->textures.east_h,
		&game->textures.east_line_len};
	if (!load_one_texture(game, game->textures.east, &tex))
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_wall_textures(game))
		return (0);
	if (has_bonus_features())
	{
		if (!load_door_texture(game))
			return (0);
		if (!load_enemy_textures(game))
			return (0);
	}
	return (1);
}

void	destroy_texture_images(t_game *game)
{
	destroy_wall_textures(game);
	if (has_bonus_features())
		destroy_bonus_textures(game);
}
