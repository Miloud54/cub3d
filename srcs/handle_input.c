/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:56:02 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/25 18:01:23 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	mouse_look(t_game *game)
{
	int		current_x;
	int		current_y;
	int		delta_x;
	double	rotation_angle;

	if (!game->mouse_enabled)
		return ;
	mlx_mouse_get_pos(game->mlx, game->window, &current_x, &current_y);
	delta_x = current_x - game->last_mouse_x;
	if (delta_x != 0)
	{
		rotation_angle = delta_x * MOUSE_SENSITIVITY;
		game->player.dir_x = game->player.dir_x * cos(rotation_angle)
			- game->player.dir_y * sin(rotation_angle);
		game->player.dir_y = game->player.dir_x * sin(rotation_angle)
			+ game->player.dir_y * cos(rotation_angle);
		game->player.plane_x = game->player.plane_x * cos(rotation_angle)
			- game->player.plane_y * sin(rotation_angle);
		game->player.plane_y = game->player.plane_x * sin(rotation_angle)
			+ game->player.plane_y * cos(rotation_angle);
	}
	game->last_mouse_x = current_x;
	if (current_x < 200 || current_x > game->win_w - 200)
	{
		mlx_mouse_move(game->mlx, game->window, game->win_w / 2, game->win_h
			/ 2);
		game->last_mouse_x = game->win_w / 2;
	}
}

int	mouse_hook(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		game->mouse_enabled = !game->mouse_enabled;
		if (game->mouse_enabled)
		{
			mlx_mouse_hide(game->mlx, game->window);
			mlx_mouse_move(game->mlx, game->window, game->win_w / 2, game->win_h
				/ 2);
			game->last_mouse_x = game->win_w / 2;
		}
		else
			mlx_mouse_show(game->mlx, game->window);
	}
	return (0);
}

void	handle_input(t_game *game)
{
	process_input(game);
	if (BONUS)
		mouse_look(game);
}
