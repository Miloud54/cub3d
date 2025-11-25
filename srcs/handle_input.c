/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:56:02 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/25 15:40:00 by edidier          ###   ########.fr       */
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

void	handle_input(t_game *game)
{
	process_input(game);
}
