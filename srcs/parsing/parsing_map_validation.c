/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:02:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/28 13:56:13 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

#if BONUS
static int	is_door(char c)
{
	return (c == 'D' || c == 'd');
}
#else
static int	is_door(char c)
{
	(void)c;
	return (0);
}
#endif

static int	can_mark(char **map, char **exterior_map, int height, int row,
		int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return (0);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (0);
	if (map[row][col] == '1' || is_door(map[row][col]))
		return (0);
	if (exterior_map[row][col] == 'X')
		return (0);
	return (1);
}

#if BONUS
static char	get_tile(char **map, int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height)
		return (' ');
	len = ft_strlen(map[row]);
	if (col < 0 || col >= len)
		return (' ');
	return (map[row][col]);
}

static int	is_wall_char(char c)
{
	return (c == '1');
}

static int	validate_door_position(char **map, int height, int row, int col)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_tile(map, height, row - 1, col);
	down = get_tile(map, height, row + 1, col);
	left = get_tile(map, height, row, col - 1);
	right = get_tile(map, height, row, col + 1);
	if ((is_wall_char(left) && is_wall_char(right)) || (is_wall_char(up)
			&& is_wall_char(down)))
		return (1);
	return (print_error("Door must be placed between two walls"));
}
#endif

static int	flood_fill_exterior(char **map, char **exterior_map, int height,
		int max_width)
{
	t_point	*queue;
	int		capacity;
	int		head;
	int		tail;
	int		row;
	int		col;
	t_point	p;

	capacity = height * max_width;
	queue = malloc(sizeof(t_point) * (capacity > 0 ? capacity : 1));
	if (!queue)
		return (0);
	head = 0;
	tail = 0;
	row = 0;
	while (row < height)
	{
		if (can_mark(map, exterior_map, height, row, 0))
		{
			exterior_map[row][0] = 'X';
			queue[tail++] = (t_point){row, 0};
		}
		col = (int)ft_strlen(map[row]) - 1;
		if (col >= 0 && can_mark(map, exterior_map, height, row, col))
		{
			exterior_map[row][col] = 'X';
			queue[tail++] = (t_point){row, col};
		}
		row++;
	}
	col = 0;
	while (col < max_width)
	{
		if (can_mark(map, exterior_map, height, 0, col))
		{
			exterior_map[0][col] = 'X';
			queue[tail++] = (t_point){0, col};
		}
		if (can_mark(map, exterior_map, height, height - 1, col))
		{
			exterior_map[height - 1][col] = 'X';
			queue[tail++] = (t_point){height - 1, col};
		}
		col++;
	}
	while (head < tail)
	{
		p = queue[head++];
		if (can_mark(map, exterior_map, height, p.row - 1, p.col))
		{
			exterior_map[p.row - 1][p.col] = 'X';
			queue[tail++] = (t_point){p.row - 1, p.col};
		}
		if (can_mark(map, exterior_map, height, p.row + 1, p.col))
		{
			exterior_map[p.row + 1][p.col] = 'X';
			queue[tail++] = (t_point){p.row + 1, p.col};
		}
		if (can_mark(map, exterior_map, height, p.row, p.col - 1))
		{
			exterior_map[p.row][p.col - 1] = 'X';
			queue[tail++] = (t_point){p.row, p.col - 1};
		}
		if (can_mark(map, exterior_map, height, p.row, p.col + 1))
		{
			exterior_map[p.row][p.col + 1] = 'X';
			queue[tail++] = (t_point){p.row, p.col + 1};
		}
	}
	free(queue);
	return (1);
}

static char	**create_exterior_map(t_game *game)
{
	char	**exterior_map;
	int		row;

	if (game->map_width == 0 || game->map_height == 0)
		return (NULL);
	exterior_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!exterior_map)
		return (NULL);
	row = 0;
	while (row < game->map_height)
	{
		exterior_map[row] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!exterior_map[row])
		{
			while (--row >= 0)
				free(exterior_map[row]);
			free(exterior_map);
			return (NULL);
		}
		row++;
	}
	exterior_map[game->map_height] = NULL;
	if (!flood_fill_exterior(game->map, exterior_map, game->map_height,
			game->map_width))
	{
		free_exterior_map(exterior_map, game->map_height);
		return (NULL);
	}
	return (exterior_map);
}

void	free_exterior_map(char **exterior_map, int height)
{
	int	row;

	if (!exterior_map)
		return ;
	row = 0;
	while (row < height)
		free(exterior_map[row++]);
	free(exterior_map);
}

static int	is_void_with_exterior_check(char **map, char **exterior_map,
		int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return (1);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (1);
	if (map[row][col] == '1')
		return (0);
	if (map[row][col] == ' ' && exterior_map[row][col] == 'X')
		return (1);
	return (0);
}

static int	validate_cell_with_exterior(char **map, char **exterior_map,
		int height, int row, int col)
{
	if (is_void_with_exterior_check(map, exterior_map, height, row - 1, col)
		|| is_void_with_exterior_check(map, exterior_map, height, row + 1, col)
		|| is_void_with_exterior_check(map, exterior_map, height, row, col - 1)
		|| is_void_with_exterior_check(map, exterior_map, height, row, col + 1))
		return (print_error("Map not closed: player/floor space adjacent to exterior"));
	return (1);
}

int	validate_map_structure(t_game *game)
{
	char	**exterior_map;
	int		player_count;
	int		row;
	int		col;

	player_count = 0;
	exterior_map = create_exterior_map(game);
	if (!exterior_map)
		return (print_error("Failed to create exterior map"));
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (is_player(game->map[row][col]))
				player_count++;
			if ((game->map[row][col] == '0' || is_player(game->map[row][col])
					|| is_door(game->map[row][col])
#if BONUS
					|| game->map[row][col] == ENEMY_SPAWN_CHAR
#endif
					) &&
				!validate_cell_with_exterior(game->map, exterior_map,
					game->map_height, row, col))
			{
				free_exterior_map(exterior_map, game->map_height);
				return (0);
			}
#if BONUS
			if (is_door(game->map[row][col])
				&& !validate_door_position(game->map, game->map_height, row,
					col))
			{
				free_exterior_map(exterior_map, game->map_height);
				return (0);
			}
#endif
			col++;
		}
		row++;
	}
	if (game->exterior_map)
		free_exterior_map(game->exterior_map, game->map_height);
	if (player_count != 1)
	{
		free_exterior_map(exterior_map, game->map_height);
		return (print_error("Map must contain exactly one player"));
	}
	game->exterior_map = exterior_map;
	return (1);
}

int	is_exterior_space(t_game *game, int row, int col)
{
	if (row < 0 || row >= game->map_height || col < 0)
		return (1);
	if (col >= (int)ft_strlen(game->map[row]))
		return (1);
	if (game->map[row][col] != ' ')
		return (0);
	if (!game->exterior_map)
		return (1);
	return (game->exterior_map[row][col] == 'X');
}
