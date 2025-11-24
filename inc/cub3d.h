/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 15:39:28 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 64
# define MAX_MAP_WIDTH 32
# define MAX_MAP_HEIGHT 17
# define COLOR_WHITESPACES " \t\n\r\v\f"

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_textures;

typedef struct s_player
{
	double		x;			// Position X dans la map (coordonnées réelles)
	double		y;			// Position Y dans la map (coordonnées réelles)
	double		dir_x;		// Vecteur direction X
	double		dir_y;		// Vecteur direction Y  
	double		plane_x;	// Vecteur plan caméra X (perpendiculaire à direction)
	double		plane_y;	// Vecteur plan caméra Y (perpendiculaire à direction)
	char		start_dir;	// Direction initiale (N/S/E/W)
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	char		**map;
	int			map_width;
	int			map_height;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	t_player	player;
	void		*useless;
}				t_game;

typedef struct s_map
{
	int			started;
	int			ended;
	int			height;
	int			width;
}				t_map;

typedef struct s_scene
{
	t_game		*game;
	t_list		*map_lines;
	int			map_started;
	int			map_height;
	int			map_width;
	int			floor_found;
	int			ceiling_found;
}				t_scene;

int				init_game(t_game *game);
int				print_error(char *msg);
int				handle_input(int keycode, t_game *game);
int				close_game(t_game *game);
int				render_map(t_game *game);

// Parsing
int				is_numeric_string(char *str);
char			*skip_spaces(char *str);
int				parse_color_line(char *line, char identifier,
					int *target_color);
int				parse_rgb_triplet(char *value_str, int *out_color);
int				is_map_identifier(char *line);
int				validate_map_line(char *line);
char			*dup_map_line(char *line);
int				append_map_line(t_list **lines, char *line, int *max_width);
char			**list_to_array(t_list **lines, int height);
int				validate_map_structure(t_game *game);
int				validate_textures(t_textures *textures);
int				handle_texture_line(char *trimmed, t_game *game);
int				handle_color_line(char *trimmed, t_scene *state);
int				looks_like_map_line(char *line);
int				process_map_line(char *line, t_scene *state);
int				file_exists(const char *path);
int				is_valid_extension(char *filename);
int				is_valid_extension_xpm(char *filename);
int				parse_scene(const char *filename, t_game *game);
int				extract_player_position(t_game *game);
int				is_exterior_space(t_game *game, int row, int col);

// Freeing functions
void			free_map(char **map);
void			free_textures(t_textures *textures);
void			cleanup_game(t_game *game);

#endif
