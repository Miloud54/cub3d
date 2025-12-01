/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exterior_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:32:35 by edidier           #+#    #+#             */
/*   Updated: 2025/12/01 14:11:38 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#if BONUS

# define BONUS_ENABLED 1

#else

# define BONUS_ENABLED 0

#endif

typedef struct s_fill_state
{
	t_point	*queue;
	int		head;
	int		tail;
}			t_fill_state;

static void	push_mark(t_map *ctx, t_point *queue, int *tail, t_point pos)
{
	int		len;
	char	tile;

	if (pos.row < 0 || pos.row >= ctx->height || pos.col < 0)
		return ;
	len = ft_strlen(ctx->map[pos.row]);
	if (pos.col >= len)
		return ;
	tile = ctx->map[pos.row][pos.col];
	if (tile == '1')
		return ;
	if (BONUS_ENABLED && (tile == 'D' || tile == 'd'))
		return ;
	if (ctx->exterior_map[pos.row][pos.col] == 'X')
		return ;
	ctx->exterior_map[pos.row][pos.col] = 'X';
	queue[(*tail)++] = (t_point){pos.row, pos.col};
}

static void	enqueue_borders(t_map *ctx, t_fill_state *state, int max_width)
{
	int	row;
	int	col;

	row = -1;
	while (++row < ctx->height)
	{
		push_mark(ctx, state->queue, &state->tail, (t_point){row, 0});
		col = (int)ft_strlen(ctx->map[row]) - 1;
		push_mark(ctx, state->queue, &state->tail, (t_point){row, col});
	}
	col = -1;
	while (++col < max_width)
	{
		push_mark(ctx, state->queue, &state->tail, (t_point){0, col});
		push_mark(ctx, state->queue, &state->tail, (t_point){ctx->height - 1,
			col});
	}
}

static void	process_queue(t_map *ctx, t_fill_state *state)
{
	t_point	p;

	while (state->head < state->tail)
	{
		p = state->queue[state->head++];
		push_mark(ctx, state->queue, &state->tail, (t_point){p.row - 1, p.col});
		push_mark(ctx, state->queue, &state->tail, (t_point){p.row + 1, p.col});
		push_mark(ctx, state->queue, &state->tail, (t_point){p.row, p.col - 1});
		push_mark(ctx, state->queue, &state->tail, (t_point){p.row, p.col + 1});
	}
}

static int	flood_fill_exterior(t_map *ctx, int max_width)
{
	t_fill_state	state;
	int				capacity;

	capacity = ctx->height * max_width;
	if (capacity < 1)
		capacity = 1;
	state.queue = malloc(sizeof(t_point) * capacity);
	if (!state.queue)
		return (0);
	state.head = 0;
	state.tail = 0;
	enqueue_borders(ctx, &state, max_width);
	process_queue(ctx, &state);
	free(state.queue);
	return (1);
}

char	**create_exterior_map(t_game *game)
{
	t_map	ctx;
	char	**exterior_map;
	int		row;

	if (game->map_width == 0 || game->map_height == 0)
		return (NULL);
	exterior_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!exterior_map)
		return (NULL);
	row = -1;
	while (++row < game->map_height)
	{
		exterior_map[row] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!exterior_map[row])
		{
			while (--row >= 0)
				free(exterior_map[row]);
			return (free(exterior_map), NULL);
		}
	}
	exterior_map[game->map_height] = NULL;
	ctx = (t_map){game->map, exterior_map, game->map_height};
	if (!flood_fill_exterior(&ctx, game->map_width))
		return (free_exterior_map(exterior_map, game->map_height), NULL);
	return (exterior_map);
}
