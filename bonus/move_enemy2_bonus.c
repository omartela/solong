/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:05:39 by omartela          #+#    #+#             */
/*   Updated: 2024/07/24 10:11:48 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

static char	check_diagonal(t_img *obs, t_img *enemy, int dx, int dy)
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

static char	check_vertical(t_img *obs, t_img *enemy, int dy)
{
	if (dy < 0 && !check_obstacle(obs, enemy, -T_SIZE, 'y'))
		return ('u');
	if (dy > 0 && !check_obstacle(obs, enemy, T_SIZE, 'y'))
		return ('d');
	if (!check_obstacle(obs, enemy, -T_SIZE, 'x'))
		return ('l');
	if (!check_obstacle(obs, enemy, T_SIZE, 'x'))
		return ('r');
	return ('r');
}

static char	check_horizontal(t_img *obs, t_img *enemy, int dx)
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
	//t_img	*obs;
	int		dx;
	int		dy;
	char	direction;

	direction = 'r';
	//obs = (t_img *)game->llist->next->next->content;
	player = (t_img *)game->llist->content;
	enemy = (t_img *)game->llist->next->next->next->next->content;
	dx = player->image->instances[0].x - enemy->image->instances[0].x;
	dy = player->image->instances[0].y - enemy->image->instances[0].y;
	if (player->image->instances[0].x == enemy->image->instances[0].x)
		direction = check_vertical(game->llist->next->next->content, enemy, dy);
	else if (player->image->instances[0].y == enemy->image->instances[0].y)
		direction = check_horizontal(game->llist->next->next->content, enemy, dy);
	else
		direction = check_diagonal(game->llist->next->next->content, enemy, dx, dy);
	return (direction);
}
