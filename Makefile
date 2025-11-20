NAME			= cub3D
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
				$(SRC_DIR)/handle_input.c \
				$(SRC_DIR)/close.c \
				$(SRC_DIR)/frees.c \
				$(SRC_DIR)/parsing/check_extension.c \
				$(SRC_DIR)/parsing/check_file_existence.c \
				$(SRC_DIR)/parsing/parsing_utils.c \
				$(SRC_DIR)/parsing/parsing_textures.c \
				$(SRC_DIR)/parsing/parsing_textures_utils.c \
				$(SRC_DIR)/parsing/parsing_colors.c \
				$(SRC_DIR)/parsing/parsing_colors_utils.c \
				$(SRC_DIR)/parsing/parsing_map.c \
				$(SRC_DIR)/parsing/parsing_map_storage.c \
				$(SRC_DIR)/parsing/parsing_map_utils.c \
				$(SRC_DIR)/parsing/parsing_map_validation.c


OBJS			= $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

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

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

run: $(NAME)
	./$(NAME) $(MAP)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
