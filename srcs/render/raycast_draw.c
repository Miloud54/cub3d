/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 15:55:24 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ensure_player_defaults(t_game *game)
{
	if (game->player.dir_x == 0.0 && game->player.dir_y == 0.0)
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
}

static void	draw_wall_pixel(t_game *game, int x, int y, t_draw_params *p)
{
	int	tex_y;
	int	tmp;

	tmp = (int)p->tex_pos;
	if (tmp < 0 || tmp >= p->t.height)
		tmp = 0;
	tex_y = tmp % p->t.height;
	p->tex_pos += p->step;
	if (p->use_texture)
		put_pixel(game, x, y, get_texel(&p->t, p->tex_x, tex_y,
				game->textures.bpp));
	else
		put_pixel(game, x, y, p->fallback_color);
}

void	draw_column(t_game *game, int x, t_draw *d, t_ray *ray)
{
	int				y;
	double			wall_x;
	t_draw_params	p;

	y = 0;
	p.t = select_texture(game, ray);
	p.fallback_color = get_fallback_color(ray);
	p.use_texture = (p.t.addr != NULL);
	wall_x = calculate_wall_x(game, ray);
	p.tex_x = calculate_tex_x(ray, wall_x, p.t.width);
	p.step = (double)p.t.height / d->line_height;
	p.tex_pos = (d->draw_start - game->win_h / 2 + d->line_height / 2) * p.step;
	while (y < game->win_h)
	{
		if (y < d->draw_start)
			put_pixel(game, x, y, game->ceiling_color);
		else if (y > d->draw_end)
			put_pixel(game, x, y, game->floor_color);
		else
			draw_wall_pixel(game, x, y, &p);
		y++;
	}
}
