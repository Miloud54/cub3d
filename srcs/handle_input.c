/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:56:02 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/25 13:31:24 by edidier          ###   ########.fr       */
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
	if (game->map[map_y][map_x] == ' ' && is_exterior_space(game, map_y, map_x))
		return (0);
	return (1);
}

static void	move_forward_backward(t_game *game, int forward)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = forward ? MOVE_SPEED : -MOVE_SPEED;
	new_x = game->player.x + game->player.dir_x * move_speed;
	new_y = game->player.y + game->player.dir_y * move_speed;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

static void	move_left_right(t_game *game, int right)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = right ? MOVE_SPEED : -MOVE_SPEED;
	new_x = game->player.x + game->player.plane_x * move_speed;
	new_y = game->player.y + game->player.plane_y * move_speed;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

// Rotation de la caméra
static void	rotate_camera(t_game *game, int right)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = right ? ROT_SPEED : -ROT_SPEED;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

static void	process_input(t_game *game)
{
	if (game->key_w)
		move_forward_backward(game, 1);
	if (game->key_s)
		move_forward_backward(game, 0);
	if (game->key_a)
		move_left_right(game, 0);
	if (game->key_d)
		move_left_right(game, 1);
	if (game->key_left)
		rotate_camera(game, 0);
	if (game->key_right)
		rotate_camera(game, 1);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (close_game(game));
	if (keycode == KEY_W)
		game->key_w = 1;
	else if (keycode == KEY_S)
		game->key_s = 1;
	else if (keycode == KEY_A)
		game->key_a = 1;
	else if (keycode == KEY_D)
		game->key_d = 1;
	else if (keycode == KEY_LEFT)
		game->key_left = 1;
	else if (keycode == KEY_RIGHT)
		game->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = 0;
	else if (keycode == KEY_S)
		game->key_s = 0;
	else if (keycode == KEY_A)
		game->key_a = 0;
	else if (keycode == KEY_D)
		game->key_d = 0;
	else if (keycode == KEY_LEFT)
		game->key_left = 0;
	else if (keycode == KEY_RIGHT)
		game->key_right = 0;
	return (0);
}

void	handle_input(t_game *game)
{
	process_input(game);
}
