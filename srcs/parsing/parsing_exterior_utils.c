/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exterior_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:33:40 by edidier           #+#    #+#             */
/*   Updated: 2025/12/01 14:11:35 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
