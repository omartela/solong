/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:57:13 by omartela          #+#    #+#             */
/*   Updated: 2024/07/18 14:49:12 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static void	move_enemy_up(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, -T_SIZE, 'y' ))
	{
		enemy->image->instances[0].y -= T_SIZE;
		enemy->previous_dir = 'u';
	}
}

static void	move_enemy_down(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, T_SIZE, 'y' ))
	{
		enemy->image->instances[0].y += T_SIZE;
		enemy->previous_dir = 'd';
	}
}

static void	move_enemy_left(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, -T_SIZE, 'x' ))
	{
		enemy->image->instances[0].x -= T_SIZE;
		if (!animation('l', game->llist->next->next->next->next->content))
			exit_game(game, 1);
		enemy->previous_dir = 'l';
	}
}

static void	move_enemy_right(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, T_SIZE, 'x' ))
	{
		enemy->image->instances[0].x += T_SIZE;
		if (!animation('r', game->llist->next->next->next->next->content))
			exit_game(game, 1);
		enemy->previous_dir = 'r';
	}
}

void	move_enemy(void *content)
{
	t_img						*enemy;
	t_game						*game;
	char						direction;

	game = (t_game *)content;
	enemy = game->llist->next->next->next->next->content;
	direction = get_direction(game);
	if (direction == 'u')
		move_enemy_up(game, enemy);
	else if (direction == 'd')
		move_enemy_down(game, enemy);
	else if (direction == 'l')
		move_enemy_left(game, enemy);
	else if (direction == 'r')
		move_enemy_right(game, enemy);
}
