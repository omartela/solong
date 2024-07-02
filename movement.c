/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:25:10 by omartela          #+#    #+#             */
/*   Updated: 2024/07/02 09:06:12 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	move_up(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -T_SIZE, 'y'))
	{
		player->image->instances[0].y -= T_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		ft_putstr_fd("Move count: ", 1);
		ft_putnbr_fd(game->move_count, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	move_down(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, T_SIZE, 'y'))
	{
		player->image->instances[0].y += T_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		ft_putstr_fd("Move count: ", 1);
		ft_putnbr_fd(game->move_count, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	move_left(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, -T_SIZE, 'x'))
	{
		player->image->instances[0].x -= T_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		ft_putstr_fd("Move count: ", 1);
		ft_putnbr_fd(game->move_count, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	move_right(t_game *game)
{
	t_list	*llist;
	t_img	*player;

	llist = game->llist;
	player = llist->content;
	if (!check_obstacle(llist->next->next->content, player, T_SIZE, 'x'))
	{
		player->image->instances[0].x += T_SIZE;
		if (check_collectable(llist->next->content, player))
			game->score += 1;
		game->move_count += 1;
		ft_putstr_fd("Move count: ", 1);
		ft_putnbr_fd(game->move_count, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	ft_hook_movement(mlx_key_data_t keydata, void *param)
{
	t_img	*player;
	t_game	*game;
	int		flag;

	flag = 0;
	game = (t_game *)param;
	player = (t_img *)game->llist->content;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		flag = 1;
	if (check_exit(game, player))
		flag = 1;
	exit_game(game, flag);
}
