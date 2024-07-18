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

unsigned int	seed = 100;

unsigned int	lcg(void)
{
	seed = (LCG_A * seed + (int)mlx_get_time() + LCG_C) % LCG_M;
	return (seed);
}

int	generate_random_number(int min, int max)
{
	return (min + (lcg() % (max - min + 1)));
}

char	get_direction_from_num(int number)
{
	number = number % 4;
	if (number == 1)
		return ('u');
	if (number == 2)
		return ('d');
	if (number == 3)
		return ('l');
	if (number == 4)
		return ('r');
	return ('r');
}

void	move_enemy_up(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, -TILE_SIZE, 'y' ))
	{
		enemy->image->instances[0].y -= TILE_SIZE;
		enemy->previous_dir = 'u';
	}
}

void	move_enemy_down(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, TILE_SIZE, 'y' ))
	{
		enemy->image->instances[0].y += TILE_SIZE;
		enemy->previous_dir = 'd';
	}
}

void	move_enemy_left(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, -TILE_SIZE, 'x' ))
	{
		enemy->image->instances[0].x -= TILE_SIZE;
		animation('l', game->llist->next->next->next->next->content);
		enemy->previous_dir = 'l';
	}
}

void	move_enemy_right(t_game *game, t_img *enemy)
{
	t_img	*obs;

	obs = (t_img *)game->llist->next->next->content;
	if (!check_obstacle(obs, enemy, TILE_SIZE, 'x' ))
	{
		enemy->image->instances[0].x += TILE_SIZE;
		animation('r', game->llist->next->next->next->next->content);
		enemy->previous_dir = 'r';
	}
}

void	move_enemy(void *content)
{
	int		number;
	t_img	*enemy;
	t_game	*game;
	char	direction;

	game = (t_game *)content;
	enemy = game->llist->next->next->next->next->content;
	number = generate_random_number(1, 4);
	direction = get_direction_from_num(number);
	seed += 1;
	while (direction == enemy->previous_dir)
		direction = get_direction_from_num(generate_random_number(-100000, 100000));
	if (direction == 'u')
		move_enemy_up(game, enemy);
	else if (direction == 'd')
		move_enemy_down(game, enemy);
	else if (direction == 'l')
		move_enemy_left(game, enemy);
	else if (direction == 'r')
		move_enemy_right(game, enemy);
}
