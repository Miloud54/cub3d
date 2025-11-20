/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by edidier           #+#    #+#             */
/*   Updated: 2025/11/20 12:16:38 by emiliedidie      ###   ########.fr       */
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
# define COLOR_WHITESPACES " \t\n\r\v\f"

typedef struct	s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct	s_game
{
	void		*mlx;
	void		*window;
	char		**map;
	int			map_width;
	int			map_height;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	void		*useless;
}	t_game;

int		init_game(t_game *game);
int		print_error(char *msg);
int		is_valid_extension(char *filename);
int		handle_input(int keycode, t_game *game);
int		close_game(t_game *game);
char	**load_map(const char *filename);

//Parsing/parsing_utils functions:
int is_numeric_string(char *str);
char	*skip_spaces(char *str);

//Parsing/check_colors functions:
int		parse_colors(const char *filename, int *floor_color, int *ceiling_color);
int		parse_rgb_triplet(char *value_str, int *out_color);

//Parsing/check_textures functions:
int		parse_textures(const char *filename, t_textures *textures);
int		validate_textures(t_textures *textures);
int		file_exists(const char *path);

//Freeing functions:
void	free_map(char **map);
void	free_textures(t_textures *textures);
void	cleanup_game(t_game *game);

#endif
