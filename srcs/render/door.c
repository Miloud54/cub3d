/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:12 by edidier           #+#    #+#             */
/*   Updated: 2025/12/01 15:24:33 by edidier          ###   ########.fr       */
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

static void	consider_door(t_game *game, int x, int y, t_door_search *s)
{
	double	dx;
	double	dy;

	if (!is_valid_cell(game, x, y))
		return ;
	if (game->map[y][x] != 'D' && game->map[y][x] != 'd')
		return ;
	dx = (x + 0.5) - game->player.x;
	dy = (y + 0.5) - game->player.y;
	if (dx * dx + dy * dy < s->best2)
	{
		s->best2 = dx * dx + dy * dy;
		s->x = x;
		s->y = y;
	}
}

static int	find_nearest_door(t_game *game, int *map_x, int *map_y)
{
	int				y;
	int				x;
	t_door_search	s;

	s = (t_door_search){DOOR_INTERACT_DIST * DOOR_INTERACT_DIST, -1, -1};
	y = (int)(game->player.y - 2);
	while (++y <= (int)(game->player.y + 2))
	{
		x = (int)(game->player.x - 2);
		while (++x <= (int)(game->player.x + 2))
			consider_door(game, x, y, &s);
	}
	*map_x = s.x;
	*map_y = s.y;
	return (s.x != -1);
}

void	toggle_door(t_game *game)
{
	int		map_x;
	int		map_y;
	double	dx;
	double	dy;

	if (!find_nearest_door(game, &map_x, &map_y))
		return ;
	dx = game->player.x - (map_x + 0.5);
	dy = game->player.y - (map_y + 0.5);
	if (dx * dx + dy * dy < (PLAYER_COLLISION_RADIUS + 0.05)
		* (PLAYER_COLLISION_RADIUS + 0.05))
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
