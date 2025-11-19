NAME			= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

SRC_DIR		= srcs
OBJ_DIR		= objs

LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

INCLUDE_DIRS	= -Iinc -I$(LIBFT_DIR)/inc -I$(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS		= $(shell find $(SRC_DIR) -name "*.c" -print)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

MAP			?= maps/valid/map1.cub
INVALID_MAPS_DIR	= maps/invalid
INVALID_MAPS	= \
	$(INVALID_MAPS_DIR)/config_after_map.cub \
	$(INVALID_MAPS_DIR)/empty_map.cub \
	$(INVALID_MAPS_DIR)/invalid_caracters.cub \
	$(INVALID_MAPS_DIR)/invalid_format.cub \
	$(INVALID_MAPS_DIR)/invalid_identifier.cub \
	$(INVALID_MAPS_DIR)/invalid_path.cub \
	$(INVALID_MAPS_DIR)/missing_walls.cub \
	$(INVALID_MAPS_DIR)/multiple_exits.cub \
	$(INVALID_MAPS_DIR)/multiple_players.cub \
	$(INVALID_MAPS_DIR)/no_ceiling.cub \
	$(INVALID_MAPS_DIR)/no_exit.cub \
	$(INVALID_MAPS_DIR)/no_item.cub \
	$(INVALID_MAPS_DIR)/no_player.cub \
	$(INVALID_MAPS_DIR)/non_rectangular.cub \
	$(INVALID_MAPS_DIR)/rgb_out_of_range.cub \
	$(INVALID_MAPS_DIR)/space.cub \
	$(INVALID_MAPS_DIR)/wrong.dada

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

run: $(NAME)
	./$(NAME) $(MAP)

test_invalid: $(NAME)
	@for file in $(INVALID_MAPS); do \
		echo ""; \
		echo "Testing $$file"; \
		./$(NAME) $$file || true; \
	done

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run test_invalid
