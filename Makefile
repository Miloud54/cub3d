NAME			= cub3D
NAME_BONUS		= cub3D_bonus
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g

SRC_DIR			= srcs
OBJ_DIR			= objs

LIBFT_DIR		= libft
MLX_DIR			= minilibx-linux

INCLUDE_DIRS	= -Iinc -I$(LIBFT_DIR)/inc -I$(MLX_DIR)
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_DIR			= srcs
OBJ_DIR			= objs

OBJ_DIRS = $(OBJ_DIR)/srcs


SRC_FILES		= \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/map_init.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/render/render.c \
				$(SRC_DIR)/render/raycast.c \
				$(SRC_DIR)/render/raycast_utils.c \
				$(SRC_DIR)/render/raycast_dda.c \
				$(SRC_DIR)/render/raycast_draw.c \
				$(SRC_DIR)/render/textures.c \
				$(SRC_DIR)/handle_input.c \
				$(SRC_DIR)/close.c \
				$(SRC_DIR)/frees.c \
				$(SRC_DIR)/parsing/check_extension.c \
				$(SRC_DIR)/parsing/check_file_existence.c \
				$(SRC_DIR)/parsing/parsing_utils.c \
				$(SRC_DIR)/parsing/parsing_textures.c \
				$(SRC_DIR)/parsing/parsing_colors.c \
				$(SRC_DIR)/parsing/parsing_colors_utils.c \
				$(SRC_DIR)/parsing/parsing_scene.c \
				$(SRC_DIR)/parsing/parsing_map_storage.c \
				$(SRC_DIR)/parsing/parsing_map_utils.c \
				$(SRC_DIR)/parsing/parsing_map_validation.c \
				$(SRC_DIR)/parsing/parsing_scene_map.c \
				$(SRC_DIR)/parsing/parsing_player.c


OBJS			= $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
OBJS_BONUS		= $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.bonus.o)

INVALID_MAPS = $(INVALID_MAPS_DIRS)/empty_map.cub \
               $(INVALID_MAPS_DIRS)/invalid_caracters.cub \
               $(INVALID_MAPS_DIRS)/invalid_format.cub \
               $(INVALID_MAPS_DIRS)/invalid_path.cub \
               $(INVALID_MAPS_DIRS)/missing_walls.cub \
               $(INVALID_MAPS_DIRS)/multiple_exits.cub \
               $(INVALID_MAPS_DIRS)/multiple_players.cub \
               $(INVALID_MAPS_DIRS)/no_exit.cub \
               $(INVALID_MAPS_DIRS)/no_player.cub \
               $(INVALID_MAPS_DIRS)/no_item.cub \
               $(INVALID_MAPS_DIRS)/space.cub \
               $(INVALID_MAPS_DIRS)/donot_exist.cub \
			   $(INVALID_MAPS_DIRS)/wrong.dada \

LIBFT			= $(LIBFT_DIR)/libft.a
MLX_LIB			= $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

DEPS			= inc/cub3d.h
DEPS_BONUS		= inc/cub3d.h inc/cub3d_bonus.h

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/$(SRC_DIR)/%.bonus.o: $(SRC_DIR)/%.c $(DEPS_BONUS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

bonus: $(LIBFT) $(MLX_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)

run: $(NAME)
	./$(NAME) $(MAP)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re run
