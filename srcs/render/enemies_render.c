/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:15:00 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 15:24:25 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static unsigned int	get_enemy_texel(t_game *game, int frame, int tex_x,
			int tex_y)
{
	char	*addr;
	int		line_len;
	int		w;
	int		h;

	w = game->textures.enemy_w;
	h = game->textures.enemy_h;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= w)
		tex_x = w - 1;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= h)
		tex_y = h - 1;
	addr = game->textures.enemy_addr[frame];
	line_len = game->textures.enemy_line_len[frame];
	return (*(unsigned int *)(addr + tex_y * line_len + tex_x
		* (game->textures.bpp / 8)));
}

static int	fill_sprite(t_game *game, t_enemy *enemy, t_sprite *s)
{
	double	inv_det;

	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	s->transform_x = inv_det * (game->player.dir_y
			* (enemy->x - game->player.x) - game->player.dir_x
			* (enemy->y - game->player.y));
	s->transform_y = inv_det * (-game->player.plane_y
			* (enemy->x - game->player.x) + game->player.plane_x
			* (enemy->y - game->player.y));
	if (s->transform_y <= 0.1)
		return (0);
	s->screen_x = (int)((game->win_w / 2) * (1 + s->transform_x
				/ s->transform_y));
	s->height = abs((int)(game->win_h / s->transform_y));
	s->width = s->height;
	s->start_y = (int)fmax(0, (double)(game->win_h - s->height) / 2);
	s->end_y = (int)fmin((double)game->win_h,
			(double)s->start_y + s->height);
	s->start_x = (int)fmax(0, (double)s->screen_x - s->width / 2);
	s->end_x = (int)fmin((double)game->win_w,
			(double)s->start_x + s->width);
	s->transparent = get_enemy_texel(game, enemy->frame, 0, 0);
	return (1);
}

static void	draw_sprite_column(t_game *game, t_enemy *enemy, t_sprite *s, int x)
{
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				step;

	tex_x = (int)((x - (-s->width / 2 + s->screen_x))
			* game->textures.enemy_w / s->width);
	if (s->transform_y <= 0 || x <= 0 || x >= game->win_w
		|| s->transform_y >= game->z_buffer[x])
		return ;
	step = game->img_bpp / 8;
	y = s->start_y - 1;
	while (++y < s->end_y)
	{
		tex_y = ((y * 2 - game->win_h + s->height) * game->textures.enemy_h)
			/ (2 * s->height);
		color = get_enemy_texel(game, enemy->frame, tex_x, tex_y);
		if (color != s->transparent)
			*(unsigned int *)(game->img_addr + (y * game->img_line_len
						+ x * step)) = color;
	}
}

static void	draw_one_enemy(t_game *game, t_enemy *enemy)
{
	t_sprite	s;
	int			x;

	if (!fill_sprite(game, enemy, &s))
		return ;
	x = s.start_x;
	while (x < s.end_x)
	{
		draw_sprite_column(game, enemy, &s, x);
		x++;
	}
}

void	draw_enemies(t_game *game)
{
	int	i;

	if (!game->enemies || game->enemy_count == 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		draw_one_enemy(game, &game->enemies[i]);
		i++;
	}
}
