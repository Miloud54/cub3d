/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:40:00 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 13:56:56 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#if BONUS

# define BONUS_ENABLED 1

#else

# define BONUS_ENABLED 0

#endif

static int	is_blocked_cell(t_game *game, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= game->map_height || map_x < 0)
		return (1);
	row_len = (int)ft_strlen(game->map[map_y]);
	if (map_x >= row_len)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	if (BONUS_ENABLED && game->map[map_y][map_x] == 'D')
		return (1);
	if (game->map[map_y][map_x] == ' ' && is_exterior_space(game, map_y,
			map_x))
		return (1);
	return (0);
}

static int	can_stand(t_game *game, double x, double y)
{
	const double	offsets[2] = {-PLAYER_COLLISION_RADIUS,
		PLAYER_COLLISION_RADIUS};
	int				i;
	int				j;

	if (!BONUS_ENABLED)
	{
		if (x < 0.0 || y < 0.0 || y >= game->map_height || x >= game->map_width)
			return (0);
		return (!is_blocked_cell(game, (int)x, (int)y));
	}
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (is_blocked_cell(game, (int)(x + offsets[i]),
				(int)(y + offsets[j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	move_forward_backward(t_game *game, int forward)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (!forward)
		move_speed = -MOVE_SPEED;
	new_x = game->player.x + game->player.dir_x * move_speed;
	new_y = game->player.y + game->player.dir_y * move_speed;
	if (can_stand(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_stand(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_left_right(t_game *game, int right)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (!right)
		move_speed = -MOVE_SPEED;
	new_x = game->player.x + game->player.plane_x * move_speed;
	new_y = game->player.y + game->player.plane_y * move_speed;
	if (can_stand(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_stand(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	rotate_camera_angle(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
}
