/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_movement_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:40:35 by omartela          #+#    #+#             */
/*   Updated: 2024/07/24 11:54:23 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	check_move(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(game);
}

void	ft_hook_movement(mlx_key_data_t keydata, void *param)
{
	t_img	*player;
	t_game	*game;
	t_img	*enemy;
	int		flag;

	flag = 0;
	game = (t_game *)param;
	player = (t_img *)game->llist->content;
	enemy = game->llist->next->next->next->next->content;
	if (keydata.action == MLX_PRESS)
		move_enemy(game);
	if (check_collision_to_player(enemy, player))
		flag = 1;
	check_move(keydata, game);
	print_moves_and_score(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		flag = 1;
	if (check_exit(game, player))
		flag = 1;
	exit_game(game, flag);
}
