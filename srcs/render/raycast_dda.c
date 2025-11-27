/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/25 18:23:18 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*DDA = Digital Differential Analyzer,
	l’algorithme de raycasting qui avance case par case dans la grille*/

void	perform_dda(t_game *game, t_ray *ray)
{
	int (hit) = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
		{
			ray->hit_tile = '1';
			if (ray->map_y >= 0 && ray->map_y < game->map_height
				&& ray->map_x >= 0
				&& ray->map_x < (int)ft_strlen(game->map[ray->map_y]))
				ray->hit_tile = game->map[ray->map_y][ray->map_x];
			hit = 1;
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
}

void	compute_draw_limits(t_game *game, t_ray *ray, t_draw *draw)
{
	draw->line_height = (int)(game->win_h / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + game->win_h / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + game->win_h / 2;
	if (draw->draw_end >= game->win_h)
		draw->draw_end = game->win_h - 1;
}
