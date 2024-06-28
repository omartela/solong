/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:25:10 by omartela          #+#    #+#             */
/*   Updated: 2024/06/28 12:19:18 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	move_up(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -TILE_SIZE, 'y'))
	{
		player->image->instances[0].y -= TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
	}
}

void	print_moves_and_score(t_game *game)
{
	mlx_image_t	*img;

	if (game->move_count_image)
		mlx_delete_image(game->mlx, game->move_count_image);
	img = mlx_put_string(game->mlx, ft_itoa(game->move_count), 12 * 10, 0);
	game->move_count_image = img;
	if (game->score_image)
		mlx_delete_image(game->mlx, game->score_image);
	img = mlx_put_string(game->mlx, ft_itoa(game->score), 25 * 10, 0);
	game->score_image = img;
}

void	move_down(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, TILE_SIZE, 'y'))
	{
		player->image->instances[0].y += TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
	}
}

void	move_left(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -TILE_SIZE, 'x'))
	{
		player->image->instances[0].x -= TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		animation('l', game->llist->content);
	}
}

void	move_right(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, TILE_SIZE, 'x'))
	{
		player->image->instances[0].x += TILE_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		animation('r', game->llist->content);
	}
}

void	ft_hook_movement(mlx_key_data_t keydata, void *param)
{
	t_img	*player;
	t_game	*game;
	t_list	*llist;
	t_img	*enemy;

	game = (t_game *)param;
	llist = game->llist;
	player = (t_img *)llist->content;
	enemy = llist->next->next->next->next->content;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(game);
	if (keydata.action == MLX_PRESS)
		move_enemy(game);
	if (check_collision_to_player(enemy, player))
		player->image->instances[0].enabled = false;
	print_moves_and_score(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_game(game);
	check_exit(game, player);
}
