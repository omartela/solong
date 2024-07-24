/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:05:39 by omartela          #+#    #+#             */
/*   Updated: 2024/07/24 10:21:19 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static char	check_diagonal(void *obs, t_img *enemy, int dx, int dy)
{
	if (abs(dx) > abs(dy))
	{
		if (dx < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'x'))
			return ('l');
		if (dx > 0 && !check_obstacle(obs, enemy, T_SIZE, 'x'))
			return ('r');
		if (!check_obstacle(obs, enemy, -T_SIZE, 'y'))
			return ('u');
		if (!check_obstacle(obs, enemy, T_SIZE, 'y'))
			return ('d');
	}
	else
	{
		if (dy < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'y'))
			return ('u');
		if (dy > 0 && !check_obstacle(obs, enemy, T_SIZE, 'y'))
			return ('d');
		if (!check_obstacle(obs, enemy, -T_SIZE, 'x'))
			return ('l');
		if (!check_obstacle(obs, enemy, T_SIZE, 'x'))
			return ('r');
	}
	return ('r');
}

static char	check_vertical(void *obs, t_img *enemy, int dy)
{
	if (dy < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'y'))
		return ('u');
	if (dy > 0 && !check_obstacle(obs, enemy, T_SIZE, 'y'))
		return ('d');
	if (!check_obstacle(obs, enemy, -T_SIZE, 'x'))
		return ('l');
	return ('r');
}

static char	check_horizontal(void *obs, t_img *enemy, int dx)
{
	if (dx < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'x'))
		return ('l');
	if (dx > 0 && !check_obstacle(obs, enemy, T_SIZE, 'x'))
		return ('r');
	if (!check_obstacle(obs, enemy, -T_SIZE, 'y'))
		return ('u');
	if (!check_obstacle(obs, enemy, T_SIZE, 'y'))
		return ('d');
	return ('r');
}

char	get_direction(t_game *game)
{
	t_img	*player;
	t_img	*enemy;
	int		dx;
	int		dy;
	char	dir;

	dir = 'r';
	player = (t_img *)game->llist->content;
	enemy = (t_img *)game->llist->next->next->next->next->content;
	dx = player->image->instances[0].x - enemy->image->instances[0].x;
	dy = player->image->instances[0].y - enemy->image->instances[0].y;
	if (player->image->instances[0].y == enemy->image->instances[0].y)
		dir = check_horizontal(game->llist->next->next->content, enemy, dx);
	else if (player->image->instances[0].x == enemy->image->instances[0].x)
		dir = check_vertical(game->llist->next->next->content, enemy, dy);
	else
		dir = check_diagonal(game->llist->next->next->content, enemy, dx, dy);
	return (dir);
}
