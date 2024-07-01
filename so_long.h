/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:52:19 by omartela          #+#    #+#             */
/*   Updated: 2024/07/01 20:27:28 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 32
# define WALLS_SIDES "Invalid map, side walls fail\n"
# define WALLS_TOP "Invalid map, top walls fail\n"
# define WALLS_TOP_BOT "Invalid map, bottom or top walls fail\n"
# define WALLS_RECTANGLE "Invalid map, map is not rectangle\n"
# define MAP_CHARS "Invalid map, map has invalid character \n"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>

typedef struct s_bfs
{
	int	front;
	int	back;
	int	q[10000][2];
	int	visited[100][100];
	int	directions[4][2];
}	t_bfs;

typedef struct s_img
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture;
}	t_img;

typedef struct s_game
{
	int			move_count;
	mlx_image_t	*move_count_image;
	int			score;
	mlx_image_t	*score_image;
	mlx_t		*mlx;
	char		**map;
	char		*filename;
	t_list		*llist;
	size_t		map_width;
	size_t		map_height;
	int			collectibles;
	size_t		players;
	size_t		exits;
	size_t		player_x;
	size_t		player_y;
}	t_game;

void	load_texture(char *str, t_img *i_s);
void	load_image(char *str, mlx_t *mlx, t_img *i_s);
void	error(char *s1);
void	load_image_to_struct(t_list **llist, char *str, mlx_t *mlx);
void	set_image_position(t_img *img, int pos_x, int pos_y);
void	insert_image_to_window(void *content, int x, int y);
int		read_map(t_game *game);
void	delete_img_node(void *content);
int		start_bfs(t_game *game);
int		validate_map_chars_and_ext(t_game *game);
int		validate_map(t_game *game);
void	free_map(char **map, size_t i);
void	extract_map_data(t_game *game, t_list **llist);
int		check_collision(mlx_image_t *obstacle, mlx_image_t *p, int i, int movement_x, int movement_y);
int		check_obstacle(void *obc, t_img *p, int movement, char direction);
int		check_collectable(void *content, t_img *p);
int		check_exit(t_game *game, t_img *p);
void	ft_hook_movement(mlx_key_data_t keydata, void *param);
void	resize_image(void *content, unsigned int x, unsigned int y);
int		check_collision_to_player(void *content, t_img *p);
int		exit_game(t_game *game, int flag);
void	free_map(char **map, size_t i);
int		init_game(t_game *game);
void	init_game_images(t_game *game, t_list **llist);
int		check_visited(t_game *game, t_bfs *bfs);
void	find_player_pos(t_game *game);
void	init_bfs(t_bfs *bfs);

#endif
