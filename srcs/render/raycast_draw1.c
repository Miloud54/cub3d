/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/11/28 15:52:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_door_tile(t_ray *ray)
{
	return (ray->hit_tile == 'D');
}

t_texinfo	get_door_texture(t_game *game)
{
	return ((t_texinfo){game->textures.door_addr, game->textures.door_w,
		game->textures.door_h, game->textures.door_line_len});
}

t_texinfo	get_wall_texture_x(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x > 0)
		return ((t_texinfo){game->textures.west_addr, game->textures.west_w,
			game->textures.west_h, game->textures.west_line_len});
	else
		return ((t_texinfo){game->textures.east_addr, game->textures.east_w,
			game->textures.east_h, game->textures.east_line_len});
}

t_texinfo	get_wall_texture_y(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y > 0)
		return ((t_texinfo){game->textures.north_addr, game->textures.north_w,
			game->textures.north_h, game->textures.north_line_len});
	else
		return ((t_texinfo){game->textures.south_addr, game->textures.south_w,
			game->textures.south_h, game->textures.south_line_len});
}

t_texinfo	select_texture(t_game *game, t_ray *ray)
{
	if (is_door_tile(ray) && game->textures.door_addr)
		return (get_door_texture(game));
	if (ray->side == 0)
		return (get_wall_texture_x(game, ray));
	else
		return (get_wall_texture_y(game, ray));
}
