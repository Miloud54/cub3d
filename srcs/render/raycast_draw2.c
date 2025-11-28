/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/11/28 15:52:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_fallback_color(t_ray *ray)
{
	if (is_door_tile(ray))
		return (0x8B5A2B);
	if (ray->side == 0)
		return (0x888888);
	return (0x555555);
}

double	calculate_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calculate_tex_x(t_ray *ray, double wall_x, int width)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = width - tex_x - 1;
	return (tex_x);
}

unsigned int	get_texel(t_texinfo *t, int tex_x, int tex_y, int bpp)
{
	char	*pixel;

	pixel = t->addr + tex_y * t->line_len + tex_x * (bpp / 8);
	return (*(unsigned int *)pixel);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->win_w || y >= game->win_h)
		return ;
	dst = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)dst = color;
}
