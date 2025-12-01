/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by edidier           #+#    #+#             */
/*   Updated: 2025/12/03 18:05:00 by edidier          ###   ########.fr       */
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
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef BONUS
#  define BONUS 1
# endif

/* Window / controls */
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_SPACE 32
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Player / movement */
# define MOVE_SPEED 0.06
# define ROT_SPEED 0.05
# define MOUSE_SENSITIVITY 0.003
# define PLAYER_COLLISION_RADIUS 0.2
# define DOOR_INTERACT_DIST 1.51

/* Minimap */
# define MINIMAP_SIZE 220
# define MINIMAP_TILE_SIZE 8
# define MINIMAP_OFFSET 24
# define MINIMAP_RADIUS 7
# define MINIMAP_TILE_SIZE_MINI 8

/* Enemy */
# define ENEMY_FRAME_COUNT 4
# define ENEMY_SPAWN_CHAR 'M'
# define ENEMY_ANIM_SPEED 0.12
# define ENEMY_MOVE_SPEED 0.75
# define ENEMY_COLLISION_RADIUS 0.2

/* Parsing */
# define COLOR_WHITESPACES " \t\n\r\v\f"

typedef struct s_point
{
	int				row;
	int				col;
}					t_point;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
	char			hit_tile;
}					t_ray;

typedef struct s_draw
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_draw;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	void			*north_img;
	void			*south_img;
	void			*west_img;
	void			*east_img;
	void			*door_img;
	char			*north_addr;
	char			*south_addr;
	char			*west_addr;
	char			*east_addr;
	char			*door_addr;
	void			*enemy_img[ENEMY_FRAME_COUNT];
	char			*enemy_addr[ENEMY_FRAME_COUNT];
	int				enemy_line_len[ENEMY_FRAME_COUNT];
	int				north_w;
	int				north_h;
	int				south_w;
	int				south_h;
	int				west_w;
	int				west_h;
	int				east_w;
	int				east_h;
	int				door_w;
	int				door_h;
	int				enemy_w;
	int				enemy_h;
	int				north_line_len;
	int				south_line_len;
	int				west_line_len;
	int				east_line_len;
	int				door_line_len;
	int				bpp;
	int				endian;
}					t_textures;

typedef struct s_texinfo
{
	char			*addr;
	int				width;
	int				height;
	int				line_len;
}					t_texinfo;

typedef struct s_tex_load
{
	void			**img;
	char			**addr;
	int				*w;
	int				*h;
	int				*line_len;
}					t_tex_load;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			start_dir;
}					t_player;

typedef struct s_enemy
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			speed;
	int				frame;
	double			frame_timer;
}					t_enemy;

typedef struct s_sprite
{
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				height;
	int				width;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
	unsigned int	transparent;
}					t_sprite;

typedef struct s_draw_params
{
	t_texinfo		t;
	int				tex_x;
	int				fallback_color;
	int				use_texture;
	double			step;
	double			tex_pos;
}					t_draw_params;

typedef struct s_fill_state
{
	t_point			*queue;
	int				head;
	int				tail;
}					t_fill_state;

typedef struct s_map
{
	char			**map;
	char			**exterior_map;
	int				height;
}					t_map;

typedef struct s_scene
{
	t_game			*game;
	t_list			*map_lines;
	int				map_started;
	int				map_height;
	int				map_width;
	int				floor_found;
	int				ceiling_found;
}					t_scene;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	int				win_w;
	int				win_h;
	char			**map;
	int				map_width;
	int				map_height;
	char			**exterior_map;
	t_textures		textures;
	t_player		player;
	int				key_w;
	int				key_s;
	int				key_a;
	int				key_d;
	int				key_left;
	int				key_right;
	int				key_interact;
	int				mouse_x;
	int				mouse_y;
	int				last_mouse_x;
	int				mouse_enabled;
	int				floor_color;
	int				ceiling_color;
	void			*img;
	char			*img_addr;
	int				img_bpp;
	int				img_line_len;
	int				img_endian;
	void			*useless;
	t_enemy			*enemies;
	int				enemy_count;
	double			*z_buffer;
	double			last_frame_time;
}					t_game;

typedef struct s_door_search
{
	double			best2;
	int				x;
	int				y;
}					t_door_search;

/* Core / init */
int					init_game(t_game *game);
int					close_game(t_game *game);
void				cleanup_game(t_game *game);

/* Input */
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					mouse_hook(int button, int x, int y, t_game *game);
void				mouse_look(t_game *game);
void				handle_input(t_game *game);

/* Rendering */
int					render_frame(t_game *game);
int					render_loop(void *param);
int					render_map(t_game *game);
void				render_minimap(t_game *game);
void				draw_enemies(t_game *game);

/* Raycasting */
void				init_ray(t_game *game, int x, t_ray *ray);
void				perform_dda(t_game *game, t_ray *ray);
void				compute_draw_limits(t_game *game, t_ray *ray, t_draw *draw);
void				draw_column(t_game *game, int x, t_draw *d, t_ray *ray);
int					is_wall(t_game *game, int x, int y);
void				ensure_player_defaults(t_game *game);

/* Textures */
int					load_textures(t_game *game);
int					load_one_texture(t_game *game, char *path, t_tex_load *tex);
int					load_door_texture(t_game *game);
int					has_bonus_features(void);
void				destroy_texture_images(t_game *game);
void				destroy_wall_textures(t_game *game);
void				destroy_bonus_textures(t_game *game);

/* Doors / interaction */
void				toggle_door(t_game *game);

/* Movement */
void				move_forward_backward(t_game *game, int forward);
void				move_left_right(t_game *game, int right);
void				rotate_camera_angle(t_game *game, double angle);

/* Enemies */
int					extract_enemies(t_game *game);
void				update_enemies(t_game *game, double dt);

/* Parsing */
int					parse_scene(const char *filename, t_game *game);
int					validate_map_structure(t_game *game);
int					validate_textures(t_textures *textures);
int					extract_player_position(t_game *game);
int					handle_texture_line(char *trimmed, t_game *game);
int					handle_color_line(char *trimmed, t_scene *state);
int					process_map_line(char *line, t_scene *state);
int					looks_like_map_line(char *line);
int					is_map_identifier(char *line);
int					validate_map_line(char *line);
char				*dup_map_line(char *line);
int					append_map_line(t_list **lines, char *line, int *max_width);
char				**list_to_array(t_list **lines, int height);
int					parse_color_line(char *line, char identifier,
						int *target_color);
int					parse_rgb_triplet(char *value_str, int *out_color);
char				*skip_spaces(char *str);
int					is_numeric_string(char *str);
int					file_exists(const char *path);
int					is_valid_extension(char *filename);
int					is_valid_extension_xpm(char *filename);
int					is_exterior_space(t_game *game, int row, int col);
void				free_exterior_map(char **exterior_map, int height);
char				**create_exterior_map(t_game *game);
int					validate_door_position(char **map, int height, int row,
						int col);

/* Drawing helpers */
int					is_door_tile(t_ray *ray);
t_texinfo			get_door_texture(t_game *game);
t_texinfo			get_wall_texture_x(t_game *game, t_ray *ray);
t_texinfo			get_wall_texture_y(t_game *game, t_ray *ray);
t_texinfo			select_texture(t_game *game, t_ray *ray);
int					get_fallback_color(t_ray *ray);
double				calculate_wall_x(t_game *game, t_ray *ray);
int					calculate_tex_x(t_ray *ray, double wall_x, int width);
unsigned int		get_texel(t_texinfo *t, int tex_x, int tex_y, int bpp);
void				put_pixel(t_game *game, int x, int y, int color);

/* Freeing helpers */
void				free_map(char **map);
void				free_textures(t_textures *textures);

int					print_error(char *msg);

#endif
