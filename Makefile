# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omartela <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 22:32:46 by omartela          #+#    #+#              #
#    Updated: 2024/06/28 15:54:32 by omartela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= solong
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code #commented for debugging -Ofast
LIBMLX	:= MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a libft/libft.a -g -lglfw -ldl -pthread -lm
SRCS	:= main.c load_images.c read_map.c validate_map.c validate_map_2.c collision.c bfs.c bfs2.c handle_images.c movement.c exit_game.c init_game.c init_game_images.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
libft:
	@make -C libft
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC)  $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
