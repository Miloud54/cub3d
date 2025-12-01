/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_door_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:32:55 by edidier           #+#    #+#             */
/*   Updated: 2025/12/01 14:11:40 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	validate_door_position(char **map, int height, int row, int col)
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
