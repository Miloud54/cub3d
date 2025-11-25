/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/25 18:39:35 by bde-la-p         ###   ########.fr       */
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
	if (game->img_addr)
		ft_bzero(game->img_addr, game->img_line_len * game->win_h);
	ensure_player_defaults(game);
	x = 0;
	while (x < game->win_w)
	{
		init_ray(game, x, &ray);
		perform_dda(game, &ray);
		compute_draw_limits(game, &ray, &draw);
		draw_column(game, x, &draw, &ray);
		x++;
	}
	if (BONUS)
		render_minimap(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_do_sync(game->mlx);
	return (1);
}

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	render_frame(game);
	return (0);
}
