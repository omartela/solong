/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:25:10 by omartela          #+#    #+#             */
/*   Updated: 2024/06/28 16:02:14 by omartela         ###   ########.fr       */
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
	char		*str;

	if (game->move_count_image)
		mlx_delete_image(game->mlx, game->move_count_image);
	str = ft_itoa(game->move_count);
	img = mlx_put_string(game->mlx, str, 12 * 10, 0);
	free(str);
	game->move_count_image = img;
	if (game->score_image)
		mlx_delete_image(game->mlx, game->score_image);
	str = ft_itoa(game->score);
	img = mlx_put_string(game->mlx, str, 25 * 10, 0);
	free(str);
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
	t_img	*enemy;
	int		flag;

	flag = 0;
	game = (t_game *)param;
	player = (t_img *)game->llist->content;
	enemy = game->llist->next->next->next->next->content;
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
	{
		flag = 1;
		player->image->instances[0].enabled = false;
	}
	print_moves_and_score(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		flag = 1;
	if (check_exit(game, player))
		flag = 1;
	exit_game(game, flag);
}
