/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:29:18 by omartela          #+#    #+#             */
/*   Updated: 2024/06/27 16:50:47 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

unsigned int	seed = 100;

unsigned int	lcg(void)
{
	seed = (LCG_A * seed + LCG_C) % LCG_M;
	return (seed);
}

int	generate_random_number(int min, int max)
{
	return (min + (lcg() % (max - min + 1)));
}

char	get_direction_from_num(int number)
{
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
		direction = get_direction_from_num(generate_random_number(1, 4));
	if (direction == 'u')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, -TILE_SIZE, 'y' ))
		{
			enemy->image->instances[0].y -= TILE_SIZE;
			enemy->previous_dir = 'u';
		}
	}
	else if (direction == 'd')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, TILE_SIZE, 'y' ))
		{
			enemy->image->instances[0].y += TILE_SIZE;
			enemy->previous_dir = 'd';
		}
	}
	else if (direction == 'l')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, -TILE_SIZE, 'x' ))
		{
			enemy->image->instances[0].x -= TILE_SIZE;
			animation('l', game->llist->next->next->next->next->content);
			enemy->previous_dir = 'l';
		}
	}
	else if (direction == 'r')
	{
		if (!check_obstacle(game->llist->next->next->content, enemy, TILE_SIZE, 'x' ))
		{
			enemy->image->instances[0].x += TILE_SIZE;
			animation('r', game->llist->next->next->next->next->content);
			enemy->previous_dir = 'r';
		}
	}
}
