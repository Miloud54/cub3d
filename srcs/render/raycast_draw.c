/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 16:29:37 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_wall_color(int side)
{
	if (side == 0)
		return (0x888888);
	return (0x555555);
}

void	draw_column(t_game *game, int x, t_draw *d, int side)
{
	int	y;

	y = 0;
	while (y < game->win_h)
	{
		if (y < d->draw_start)
			mlx_pixel_put(game->mlx, game->window, x, y, game->ceiling_color);
		else if (y > d->draw_end)
			mlx_pixel_put(game->mlx, game->window, x, y, game->floor_color);
		else
			mlx_pixel_put(game->mlx, game->window, x, y, get_wall_color(side));
		y++;
	}
}
