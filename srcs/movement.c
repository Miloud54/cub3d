/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:40:00 by edidier           #+#    #+#             */
/*   Updated: 2025/11/25 15:40:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height || map_x < 0)
		return (0);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	if (game->map[map_y][map_x] == ' '
		&& is_exterior_space(game, map_y, map_x))
		return (0);
	return (1);
}

static int	can_stand(t_game *game, double x, double y)
{
	double	offsets[2];
	int		i;
	int		j;

	offsets[0] = -PLAYER_COLLISION_RADIUS;
	offsets[1] = PLAYER_COLLISION_RADIUS;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (!is_valid_position(game, x + offsets[i], y + offsets[j]))
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

void	rotate_camera(t_game *game, int right)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = ROT_SPEED;
	if (!right)
		rot_speed = -ROT_SPEED;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}
