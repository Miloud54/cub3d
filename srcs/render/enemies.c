/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:35:00 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 13:55:53 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#if BONUS

static void	update_enemy_anim(t_enemy *enemy, double dt)
{
	enemy->frame_timer += dt;
	if (enemy->frame_timer >= ENEMY_ANIM_SPEED)
	{
		enemy->frame = (enemy->frame + 1) % ENEMY_FRAME_COUNT;
		enemy->frame_timer = 0.0;
	}
}

static void	handle_enemy_touch(t_game *game, double dx, double dy,
		double touch2)
{
	double	dist2;

	dist2 = dx * dx + dy * dy;
	if (dist2 > touch2)
		return ;
	write(1, "Game Over\n", 10);
	close_game(game);
}

static void	move_enemy(t_game *game, t_enemy *e, double dt, double r)
{
	double			new_x;
	double			new_y;

	new_x = e->x + e->dir_x * e->speed * dt;
	new_y = e->y + e->dir_y * e->speed * dt;
	if (!is_wall(game, (int)(new_x + r), (int)e->y)
		&& !is_wall(game, (int)(new_x - r), (int)e->y))
		e->x = new_x;
	else
		e->dir_x *= -1;
	if (!is_wall(game, (int)e->x, (int)(new_y + r))
		&& !is_wall(game, (int)e->x, (int)(new_y - r)))
		e->y = new_y;
	else
		e->dir_y *= -1;
}

static void	update_one_enemy(t_game *game, t_enemy *e, double dt,
		double touch2)
{
	double	r;

	r = ENEMY_COLLISION_RADIUS;
	move_enemy(game, e, dt, r);
	handle_enemy_touch(game, e->x - game->player.x, e->y - game->player.y,
		touch2);
	update_enemy_anim(e, dt);
}

void	update_enemies(t_game *game, double dt)
{
	int		i;
	double	touch2;

	if (game->enemy_count == 0 || dt <= 0.0)
		return ;
	touch2 = (PLAYER_COLLISION_RADIUS + ENEMY_COLLISION_RADIUS)
		* (PLAYER_COLLISION_RADIUS + ENEMY_COLLISION_RADIUS);
	i = 0;
	while (i < game->enemy_count)
	{
		update_one_enemy(game, &game->enemies[i], dt, touch2);
		i++;
	}
}

#endif
