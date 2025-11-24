/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by edidier           #+#    #+#             */
/*   Updated: 2025/11/24 17:00:59 by edidier          ###   ########.fr       */
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

// Contrôles joueur
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// Keycodes (Linux/X11)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
}				t_ray;

typedef struct s_draw
{
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_draw;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	void		*north_img;
	void		*south_img;
	void		*west_img;
	void		*east_img;
	char		*north_addr;
	char		*south_addr;
	char		*west_addr;
	char		*east_addr;
	int			north_w;
	int			north_h;
	int			south_w;
	int			south_h;
	int			west_w;
	int			west_h;
	int			east_w;
	int			east_h;
	int			north_line_len;
	int			south_line_len;
	int			west_line_len;
	int			east_line_len;
	int			bpp;
	int			endian;
}				t_textures;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		start_dir;
}				t_player;

typedef struct s_texinfo
{
	char		*addr;
	int			width;
	int			height;
	int			line_len;
}				t_texinfo;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			win_w;
	int			win_h;
	char		**map;
	int			map_width;
	int			map_height;
	t_textures	textures;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
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
int				render_frame(t_game *game);
int				render_loop(void *param);
int				is_wall(t_game *game, int x, int y);
void			ensure_player_defaults(t_game *game);
void			init_ray(t_game *game, int x, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			compute_draw_limits(t_game *game, t_ray *ray, t_draw *draw);
void			draw_column(t_game *game, int x, t_draw *d, t_ray *ray);
int				load_textures(t_game *game);
void			destroy_texture_images(t_game *game);

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
