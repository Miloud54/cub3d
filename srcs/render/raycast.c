/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 15:22:32 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ensure_player_defaults(t_game *game)
{
	if (game->player.dir_x == 0 && game->player.dir_y == 0)
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	if (game->player.x == 0 && game->player.y == 0)
	{
		game->player.x = 1.5;
		game->player.y = 1.5;
	}
}

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
#if BONUS
		if (game->z_buffer)
			game->z_buffer[x] = ray.perp_wall_dist;
#endif
		x++;
	}
#if BONUS
	if (BONUS)
		draw_enemies(game);
#endif
	if (BONUS)
		render_minimap(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_do_sync(game->mlx);
	return (1);
}

#if BONUS
static double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}
#endif

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
#if BONUS
	double	now;
	double	dt;

	now = get_time_seconds();
	if (game->last_frame_time <= 0.0)
		dt = 0.0;
	else
		dt = now - game->last_frame_time;
	game->last_frame_time = now;
	if (dt > 0.25)
		dt = 0.25;
	update_enemies(game, dt);
#endif
	handle_input(game);
	render_frame(game);
	return (0);
}
