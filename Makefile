# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omartela <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 22:32:46 by omartela          #+#    #+#              #
#    Updated: 2024/07/22 11:42:28 by omartela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= so_long
BONUS_NAME := so_long_bonus
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a libft/libft.a -g -lglfw -ldl -pthread -lm
SRCS	:= main.c \
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

SRCS_BONUS := bonus/animation_bonus.c \
			  bonus/bfs2_bonus.c \
			  bonus/bfs_bonus.c \
			  bonus/collision_bonus.c \
			  bonus/exit_game_bonus.c \
			  bonus/handle_images_bonus.c \
			  bonus/init_game_bonus.c \
			  bonus/init_game_images_bonus.c \
			  bonus/load_images_bonus.c \
			  bonus/main_bonus.c \
			  bonus/move_enemy2_bonus.c \
			  bonus/move_enemy_bonus.c \
			  bonus/movement_bonus.c \
			  bonus/read_map_bonus.c \
			  bonus/validate_map_2_bonus.c \
			  bonus/validate_map_bonus.c \

OBJS	:= ${SRCS:.c=.o}

BONUS_OBJS := ${SRCS_BONUS:.c=.o}

all: $(NAME)

$(LIBMLX)/build/libmlx42.a:
	@if [ ! -d "$(LIBMLX)/build" ]; then \
		cmake $(LIBMLX) -B $(LIBMLX)/build; \
		fi
	@make -C $(LIBMLX)/build -j4

libmlx: $(LIBMLX)/build/libmlx42.a

libft:
	@make -C libft && make -C libft bonus
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): libmlx libft $(OBJS)
	@$(CC)  $(OBJS) $(LIBS) -o $(NAME)

$(BONUS_NAME): libmlx libft $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)

bonus: $(BONUS_NAME)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	rm -rf $(LIBMLX)/build
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	make -C libft fclean
re: clean all

.PHONY: all clean fclean re libmlx libft
