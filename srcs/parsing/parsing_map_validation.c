/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:02:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/12/01 14:12:10 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#if BONUS

# define BONUS_ENABLED 1

#else

# define BONUS_ENABLED 0

#endif

static const t_point	g_offsets[4] = {
{-1, 0},
{1, 0},
{0, -1},
{0, 1}
};

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_door(char c)
{
	if (!BONUS_ENABLED)
		return (0);
	return (c == 'D' || c == 'd');
}

static int	validate_cell_with_exterior(t_map *ctx, int row, int col)
{
	char		*msg;
	int			i;
	int			n_row;
	int			n_col;

	msg = "Map not closed: player/floor space adjacent to exterior";
	i = 0;
	while (i < 4)
	{
		n_row = row + g_offsets[i].row;
		n_col = col + g_offsets[i].col;
		if (n_row < 0 || n_row >= ctx->height || n_col < 0)
			return (print_error(msg));
		if (n_col >= (int)ft_strlen(ctx->map[n_row]))
			return (print_error(msg));
		if (ctx->map[n_row][n_col] == ' '
			&& ctx->exterior_map[n_row][n_col] == 'X')
			return (print_error(msg));
		i++;
	}
	return (1);
}

static int	process_cell(t_game *game, t_map *ctx, t_point pos,
		int *player_count)
{
	char	tile;

	tile = game->map[pos.row][pos.col];
	if (is_player(tile))
		(*player_count)++;
	if ((tile == '0' || is_player(tile) || is_door(tile) || (BONUS_ENABLED
				&& tile == ENEMY_SPAWN_CHAR))
		&& !validate_cell_with_exterior(ctx, pos.row, pos.col))
		return (0);
	if (BONUS_ENABLED && is_door(tile) && !validate_door_position(game->map,
			game->map_height, pos.row, pos.col))
		return (0);
	return (1);
}

int	validate_map_structure(t_game *game)
{
	t_map	ctx;
	int		player_count;
	int		row;
	int		col;

	player_count = 0;
	row = -1;
	ctx = (t_map){game->map, create_exterior_map(game), game->map_height};
	if (!ctx.exterior_map)
		return (print_error("Failed to create exterior map"));
	while (++row < game->map_height)
	{
		col = -1;
		while (game->map[row][++col])
			if (!process_cell(game, &ctx, (t_point){row, col}, &player_count))
				return (free_exterior_map(ctx.exterior_map, game->map_height),
					0);
	}
	if (game->exterior_map)
		free_exterior_map(game->exterior_map, game->map_height);
	if (player_count != 1)
		return (free_exterior_map(ctx.exterior_map, game->map_height),
			print_error("Map must contain exactly one player"));
	game->exterior_map = ctx.exterior_map;
	return (1);
}
