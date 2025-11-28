/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 15:47:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	render_raycast_loop(t_game *game)
{
	int		x;
	t_ray	ray;
	t_draw	draw;

	x = 0;
	while (x < game->win_w)
	{
		init_ray(game, x, &ray);
		perform_dda(game, &ray);
		compute_draw_limits(game, &ray, &draw);
		draw_column(game, x, &draw, &ray);
		if (BONUS && game->z_buffer)
			game->z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
}

int	render_frame(t_game *game)
{
	if (!game->mlx || !game->window || !game->map)
		return (0);
	if (game->img_addr)
		ft_bzero(game->img_addr, game->img_line_len * game->win_h);
	ensure_player_defaults(game);
	render_raycast_loop(game);
	if (BONUS)
		draw_enemies(game);
	if (BONUS)
		render_minimap(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_do_sync(game->mlx);
	return (1);
}

static double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

static void	update_game_timing(t_game *game)
{
	double	now;
	double	dt;

	if (!BONUS)
		return ;
	now = get_time_seconds();
	if (game->last_frame_time <= 0.0)
		dt = 0.0;
	else
		dt = now - game->last_frame_time;
	game->last_frame_time = now;
	if (dt > 0.25)
		dt = 0.25;
	update_enemies(game, dt);
}

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_game_timing(game);
	handle_input(game);
	render_frame(game);
	return (0);
}
