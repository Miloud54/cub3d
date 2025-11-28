/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 13:56:39 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#if BONUS

static int	is_valid_cell(t_game *game, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= game->map_height || map_x < 0)
		return (0);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	return (1);
}

void	toggle_door(t_game *game)
{
	int		map_x;
	int		map_y;
	double	target_x;
	double	target_y;

	target_x = game->player.x + game->player.dir_x * DOOR_INTERACT_DIST;
	target_y = game->player.y + game->player.dir_y * DOOR_INTERACT_DIST;
	map_x = (int)target_x;
	map_y = (int)target_y;
	if (!is_valid_cell(game, map_x, map_y))
		return ;
	if (game->map[map_y][map_x] == 'D')
		game->map[map_y][map_x] = 'd';
	else if (game->map[map_y][map_x] == 'd')
		game->map[map_y][map_x] = 'D';
}

#else

void	toggle_door(t_game *game)
{
	(void)game;
}

#endif
