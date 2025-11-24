/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 17:01:05 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_texinfo	select_texture(t_game *game, t_ray *ray)
{
	t_texinfo	t;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			t = (t_texinfo){game->textures.west_addr, game->textures.west_w,
				game->textures.west_h, game->textures.west_line_len};
		else
			t = (t_texinfo){game->textures.east_addr, game->textures.east_w,
				game->textures.east_h, game->textures.east_line_len};
	}
	else
	{
		if (ray->ray_dir_y > 0)
			t = (t_texinfo){game->textures.north_addr, game->textures.north_w,
				game->textures.north_h, game->textures.north_line_len};
		else
			t = (t_texinfo){game->textures.south_addr, game->textures.south_w,
				game->textures.south_h, game->textures.south_line_len};
	}
	return (t);
}

static unsigned int	get_texel(t_texinfo *t, int tex_x, int tex_y, int bpp)
{
	char	*pixel;

	pixel = t->addr + tex_y * t->line_len + tex_x * (bpp / 8);
	return (*(unsigned int *)pixel);
}

static void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->win_w || y >= game->win_h)
		return ;
	dst = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_game *game, int x, t_draw *d, t_ray *ray)
{
	int			y;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		step;
	double		tex_pos;
	t_texinfo	t;
	int			tmp;
	int			fallback_color;

	y = 0;
	t = select_texture(game, ray);
	fallback_color = (ray->side == 0) ? 0x888888 : 0x555555;
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)t.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = t.width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = t.width - tex_x - 1;
	step = (double)t.height / d->line_height;
	tex_pos = (d->draw_start - game->win_h / 2 + d->line_height / 2) * step;
	while (y < game->win_h)
	{
		if (y < d->draw_start)
			put_pixel(game, x, y, game->ceiling_color);
		else if (y > d->draw_end)
			put_pixel(game, x, y, game->floor_color);
		else
		{
			tmp = (int)tex_pos;
			if (tmp < 0 || tmp >= t.height)
				tmp = 0;
			tex_y = tmp % t.height;
			tex_pos += step;
			if (t.addr)
				put_pixel(game, x, y, get_texel(&t, tex_x, tex_y,
						game->textures.bpp));
			else
				put_pixel(game, x, y, fallback_color);
		}
		y++;
	}
}
