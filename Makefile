# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 08:57:09 by omartela          #+#    #+#              #
#    Updated: 2024/07/31 08:57:14 by omartela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
NAMEBONUS := so_long_bonus
BONUS_DIR = ./bonus/
SRCS := main.c \
		load_images.c \
         read_map.c \
         validate_map.c \
         validate_map_2.c \
         collision.c bfs.c \
         bfs2.c \
         handle_images.c \
         movement.c \
         exit_game.c \
         init_game.c \
         init_game_images.c \

SRCS_BONUS := main_bonus.c \
			  animation_bonus.c \
              bfs2_bonus.c \
              bfs_bonus.c \
              collision_bonus.c \
              exit_game_bonus.c \
              handle_images_bonus.c \
              init_game_bonus.c \
              init_game_images_bonus.c \
              load_images_bonus.c \
              move_enemy2_bonus.c \
              move_enemy_bonus.c \
              movement_bonus.c \
              read_map_bonus.c \
              validate_map_2_bonus.c \
              validate_map_bonus.c \
              print_moves_score_bonus.c \
              init_player_images_bonus.c \
              init_enemy_images_bonus.c \
              hook_movement_bonus.c \

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(addprefix $(BONUS_DIR), $(SRCS_BONUS:.c=.o))
MLX_DIR = ./MLX42
MLX_HEADER = -I $(MLX_DIR)/include
HEADERS = -I. $(MLX_HEADER) -I$(LIBFT_DIR)
LIBMLX = $(MLX_DIR)/build/libmlx42.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OSFLAGS = -ldl -lglfw -pthread -lm
CFLAGS = -Wall -Wextra -Werror
CC = cc

all: $(LIBFT) $(LIBMLX) $(NAME)

bonus: $(LIBFT) $(LIBMLX) $(NAMEBONUS)

$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@make -C $(MLX_DIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "Compiling: $<"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBMLX) $(LIBFT) $(OSFLAGS) -o $(NAME)

$(NAMEBONUS): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBMLX) $(LIBFT) $(OSFLAGS) -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@rm -rf $(MLX_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) $(NAMEBONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re libmlx libft bonus
