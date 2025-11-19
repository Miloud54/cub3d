/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by edidier           #+#    #+#             */
/*   Updated: 2025/11/19 12:33:50 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define MAX_MAP_WIDTH 32
# define MAX_MAP_HEIGHT 17

typedef struct	s_game
{
	void	*mlx;
	void	*window;
	char	**map;
	int		map_width;
	int		map_height;
}	t_game;

int	init_game(t_game *game);
void	free_map(char **map);

#endif