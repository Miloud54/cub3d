NAME		= cub3D

BONUS		= 0

CC			= cc
CFLAGS		= -Werror -Wextra -Wall -g

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

SRC_PATH 	= ./srcs/
SRC			= 	main.c \
				map_init.c \
				utils.c \
				render/render.c \
				render/raycast.c \
				render/raycast_utils.c \
				render/raycast_dda.c \
				render/raycast_draw.c \
				render/textures.c \
				movement.c \
				handle_input.c \
				close.c \
				frees.c \
				parsing/check_extension.c \
				parsing/check_file_existence.c \
				parsing/parsing_utils.c \
				parsing/parsing_textures.c \
				parsing/parsing_colors.c \
				parsing/parsing_colors_utils.c \
				parsing/parsing_scene.c \
				parsing/parsing_map_storage.c \
				parsing/parsing_map_utils.c \
				parsing/parsing_map_validation.c \
				parsing/parsing_scene_map.c \
				parsing/parsing_player.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= ./objs/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./inc/\
				-I ./libft/\
				-I ./minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/movement
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/debug
	mkdir -p $(OBJ_PATH)/exit

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

$(LIBFT):
	make -sC $(LIBFT_PATH)

$(MLX):
	make -sC $(MLX_PATH)

bonus:
	make all BONUS=1

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean bonus
