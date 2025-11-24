/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/23 12:05:12 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;
	t_draw	draw;

	if (!game->mlx || !game->window || !game->map)
		return (0);
	ensure_player_defaults(game);
	x = 0;
	while (x < game->win_w)
	{
		init_ray(game, x, &ray);
		perform_dda(game, &ray);
		compute_draw_limits(game, &ray, &draw);
		draw_column(game, x, &draw, ray.side);
		x++;
	}
	return (1);
}

int	render_loop(t_game *game)
{
	render_frame(game);
	return (0);
}
